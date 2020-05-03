# MAP Tester

from tkinter import *			   	# GUI
import tkinter.ttk as ttk		   	# Themed GUI
from tkinter import messagebox		# Pop Up Windows
import tkinter.scrolledtext as tkst	# GUI Scrollbar
import matplotlib					# Graphing
matplotlib.use("TkAgg")				# Tk backend
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg	# Canvas
from matplotlib.figure import Figure# Graph data
import matplotlib.pyplot as plt		# Plot data
from matplotlib import style		# Style graph
import config						# Config File
import time						 	# Sleep
import datetime						# Get today's date
import threading					# Run multiple threads
import serial					   	# Serial Comms
import serial.tools.list_ports	  	# List COM ports
import subprocess				   	# Open other programs

class User():					   	# TODO: setup User constructors based on DB 
	def __init__(self):
		self._name : str
		self._id : str
		self._admin = False
		self._engineer = False
		self._maintenance = False
		self._production = False

	@property
	def name(self):
		return self._name

	@property
	def id(self):
		return self._id

	@property
	def admin(self):
		return self._admin

	@property
	def engineer(self):
		return self._engineer

	@property
	def maintenance(self):
		return self._maintenance

	@property
	def production(self):
		return self._production


class Program(Tk):				  	# TODO: Database stuff
	def __init__ (self):	                # Initialize GUI (Entire window / title block)
		Tk.__init__(self)
		self._frame = None

		### Window Setup ###
		self.configure(background = 'blue')
		w,h = self.winfo_screenwidth(), self.winfo_screenheight()	# Gathering the size of the screen
		self.geometry('%dx%d+0+0' % (w, h))	 	# Changing the Program size to match the screen
		self.geometry('%dx%d+0+0' % (1280, 1024))
		# self.state('zoomed')					# Zoom window
		# self.attributes('-fullscreen', True)	# Fullscreen window

		img = PhotoImage(file = 'MAP-Tester\\logo.gif')	 # Setting up the logo image

		# Setup widgets
		menubar = Menu(self)
		menubar.add_command(label = 'Exit', command = onClosing)
		# menubar.add_command(label = 'Logout', command = lambda: self.switch_frame(AdminPage))
		# menubar.add_command(label = 'Admin', command = lambda: self.switch_frame(AdminPage))
		# menubar.add_command(label = 'Engineering', command = lambda: self.switch_frame(EngineeringPage))
		# menubar.add_command(label = 'Maintenance', command = lambda: self.switch_frame(MaintenancePage))
		# menubar.add_command(label = 'Help')
		logoLabel = Label(self, image = img)	
		logoLabel.image = img
		titleLabel = Label(self, text = ' MAP Tester V3.0 ', background = '#006FFF', font = ('Arial', 48, 'bold'), fg = 'white', relief = RAISED)
		self.statusFrame = Frame(self, bg = 'blue')	 # Frame to hold status stuff
		self.statusLabel = Label(self.statusFrame, text = 'Status', bg = 'blue', font = 'Arial 16 bold underline', fg = 'white')
		self.standLabel = Label(self.statusFrame, text = 'Stand', bg = 'blue', font = 'Arial 16 bold', fg = 'white')
		self.standStatusLabel = Label(self.statusFrame, text = '✗', bg = 'red', font = 'Arial 16', fg = 'white')
		self.fileWritingLabel = Label(self.statusFrame, text = 'File Writing', bg = 'blue', font = 'Arial 16 bold', fg = 'white')
		self.fileStatusLabel = Label(self.statusFrame, text = '✓', bg = 'green', font = 'Arial 16', fg = 'white')

		# Setup weights
		self.columnconfigure(0, weight = 1)	 
		self.columnconfigure(1, weight = 1)
		self.rowconfigure(1, weight = 1)

		# Place widgets
		self.config(menu = menubar)			 # Place menubar
		logoLabel.grid(row = 0, column = 0, padx = 10, pady = 10, sticky = "NW")	 
		titleLabel.grid(row = 0, column = 1, padx = 10, pady = 10, sticky = "NE")
		self.statusFrame.grid(row = 1, column = 0, padx = 10, pady = 10, sticky = 'NW') 
		self.statusLabel.grid(row = 0, column = 0)
		self.standLabel.grid(row = 1, column = 0)
		self.standStatusLabel.grid(row = 1, column = 1)
		self.fileWritingLabel.grid(row = 2, column = 0)
		self.fileStatusLabel.grid(row = 2, column = 1)
		self.switch_frame(ConnectionPage)	   # Switch to ConnectionPage

	def switch_frame(self, frame_class):		# Destroys current frame, replaces with new
		new_frame = frame_class(self)
		if self._frame is not None:
			self._frame.destroy()
		self._frame = new_frame
		self._frame.grid(row = 1, column = 0, columnspan = 2)
		self._frame.config(background = 'pink')

	def readingA(self):
		while(self.transStatus > 0):
			if (self.transStatus == 0):		# Stop
				break
			if (self.transStatus == 1):	 	# Read
				try:
					self.transducer.write(bytes('FETCH?\n', 'utf8'))	# This is the command sent to the meter
					self.transducer.readline()							# Get rid of the confirmation command from the meter 
					Answer = (self.transducer.readline())				# Reading the response
					self.transValue = (float(Answer))					# Converting the latest response to a float.
				except:
					pass
				time.sleep(.01)
			if (self.transStatus == 2):	 # Standby 		
				self.transValue = 0
			continue

	def readingB(self):
		while(self.dutStatus > 0):
			if (self.dutStatus == 0):		# Stop
				break
			if (self.dutStatus == 1):	 	# Read
				try:
					self.dut.write(bytes('FETCH?\n', 'utf8'))	# This is the command sent to the meter
					self.dut.readline()							# Get rid of the confirmation command from the meter 
					Answer = (self.dut.readline())				# Reading the response
					self.dutValue = (float(Answer))					# Converting the latest response to a float.
				except:
					pass
				time.sleep(.01)
			if (self.dutStatus == 2):	 # Standby 		
				self.dutValue = 0
				continue

	def commShutdown(self):	# Shutdown com port and the thread
		try:
			self.transducer.close()	# Close the serial port to the meter
			self.dut.close()
			self.arduino.close()
			self.transStatus = 0
			self.dutStatus = 0
			self.threadA.join()
			self.threadB.join()		 
		except:
			pass


class ConnectionPage(Frame):
	def __init__(self, master):				 # Initialize ConnectionPage (Frame within window)
		Frame.__init__(self, master)

		# Setup widgets
		self.connectionLabel = Label(self, text = ' Connecting . . . ', background = 'yellow', font = ('Arial','32'), relief = GROOVE)
		self.adminButton = Button(self, text = "Open Admin page", command = lambda: master.switch_frame(AdminPage))

		# Setup weights
		self.columnconfigure(0, weight = 1)	 
		self.columnconfigure(1, weight = 1)
		self.rowconfigure(0, weight = 1)
		self.rowconfigure(1, weight = 1)

		# Place widgets
		self.connectionLabel.grid(row = 1, column = 0, columnspan = 2, sticky = 'NSEW') 

		self.after(1000, lambda: self.connections(master))   # Start connecting to serial devices

	def connections(self, master):	  # Connect to COMs, change label to status, move to next page if pass  

		### Serial Connections ###
		print('Starting Connections to the different devices . . . ')
		connected = True	# Check for connections

		# Connecting to the first Multimeter and outputting setup data
		try:
			print('Multimeter Number 1 . . . ')
			master.transducer = serial.Serial(port = config.multiCOMA, baudrate = config.BAUD, timeout = 1)	# Open the USB port that corresponds to the multimeter
			time.sleep(.1)
			print('Port:', master.transducer.name)
			master.transducer.write('FUNC VOLT:DC\n'.encode())	# Set to correct mode
			time.sleep(.1)
			if master.transducer.readline().decode() == '':	# Check that meter is connected / on
				print('ERROR: Multimeter 1 Not Connected')
				connected = False
			else:
				print('Multimeter 1 Done . . . ')
		except:
			print('ERROR: Multimeter 1 Not Connected')
			connected = False

		# Connecting to the second Multimeter and outputting setup data
		try:
			print('Multimeter Number 2 . . . ')
			master.dut = serial.Serial(port = config.multiCOMB, baudrate = config.BAUD, timeout = 1) 	# Open the USB port that corresponds to the arduino
			time.sleep(.1)
			print('Port:', master.dut.name)
			master.dut.write('FUNC VOLT:DC\n'.encode())	# Set to correct mode
			time.sleep(.1)
			if master.dut.readline().decode() == '':	# Check that meter is connected / on
				print('ERROR: Multimeter 2 Not Connected')
				connected = False
			else:
				print('Multimeter Number 2 Done . . . ')
		except:
			print('ERROR: Multimeter 2 Not Connected')
			connected = False

		# Connecting to the Arduino and outputting setup data
		print('Setup Arduino . . . ')
		try:
			master.arduino = serial.Serial(port = config.arduinoCOM, baudrate = config.arduinoBAUD, timeout = 1) 	# Open the USB port that corresponds to the arduino
			print('Port:', master.arduino.name)
			time.sleep(.1)
			master.arduino.write('V'.encode())
			time.sleep(.1)
			if master.arduino.readline().decode() == '':	# Check that meter is connected / on
				print('ERROR: Arduino Not Connected')
				connected = False
			else:
				print('Arduino Done . . . ')
		except:
			print('ERROR: Arduino Not Connected')
			connected = False

		# Check connections, start threads, move on
		if connected == True:
			self.connectionLabel.config(text = ' Connection Complete ', background = 'green', relief = GROOVE)	# Change label 
			master.standStatusLabel.config(text = '✓', bg = 'green')	# Change stand status label
			master.transStatus = 2
			master.dutStatus = 2
			master.threadA = threading.Thread(target = master.readingA, args = ())
			master.threadB = threading.Thread(target = master.readingB, args = ())
			master.threadA.start()
			master.threadB.start() 
			self.after(1000, lambda: master.switch_frame(CollectOEDataPage))	# Switch page after 3 seconds
		else:
			self.connectionLabel.config(text = ' Connection Failed ', background = 'red', relief = GROOVE)	  # Change label
			self.adminButton.grid(columnspan = 2)


class LoginPage(Frame):
	def __init__(self, master):				 # Initialize LoginPage (Frame within window)
		Frame.__init__(self, master)

		# Setup widgets

		# Setup weights

		# Place widgets

		Label(self, text = 'This is login page').grid()
		Button(self, text = "Go Back", command = lambda: master.switch_frame(ConnectionPage)).grid(row = 1) # Test button


class AdminPage(Frame):
	def __init__(self, master):				 # Initialize AdminPage (Frame within window)
		Frame.__init__(self, master)
		
		# Setup widgets
		productionButton = Button(self, text = 'Production', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 10, command = lambda: master.switch_frame(ProductionPage))
		engineeringButton = Button(self, text = 'Engineering', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 10, command = lambda: master.switch_frame(EngineeringPage))
		maintenanceButton = Button(self, text = 'Maintenance', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 10, command = lambda: master.switch_frame(MaintenancePage))
		Button(self, text = "Go Back", command = lambda: master.switch_frame(ConnectionPage)).grid(row = 1, columnspan = 3) # Test button

		# Setup weights
		self.columnconfigure(0, weight = 1)	 
		self.columnconfigure(1, weight = 1)
		self.rowconfigure(0, weight = 1)
		self.rowconfigure(1, weight = 1)

		# Place widgets
		productionButton.grid(row = 0, column = 0, padx = 10, sticky = 'NSEW')
		engineeringButton.grid(row = 0, column = 1, padx = 10, sticky = 'NSEW')
		maintenanceButton.grid(row = 0, column = 2, padx = 10, sticky = 'NSEW')


class ProductionPage(Frame):
	def __init__(self, master):				 # Initialize ProductionPage (Frame within window)
		Frame.__init__(self, master)

		# Setup widgets

		# Setup weights

		# Place widgets

		Label(self, text = 'This is production page').grid()
		Button(self, text = "Go Back", command = lambda: master.switch_frame(AdminPage)).grid(row = 1) # Test button


class EngineeringPage(Frame):
	def __init__(self, master):				 # Initialize EngineeringPage (Frame within window)
		Frame.__init__(self, master)

		# Setup widgets

		# Setup weights

		# Place widgets

		Label(self, text = 'This is engineering page').grid()
		Button(self, text = "Go Back", command = lambda: master.switch_frame(AdminPage)).grid(row = 1) # Test button


class MaintenancePage(Frame):
	def __init__(self, master):				 # Initialize MaintenancePage (Frame within window)
		Frame.__init__(self, master)

		# Setup widgets
		checkComButton = ttk.Button(self, text = 'Check COM Ports', command = lambda: master.switch_frame(ComPage))
		calibrationButton = ttk.Button(self, text = 'Run Calibration', command = lambda: master.switch_frame(CalibrationPage))
		changeTestButton = ttk.Button(self, text = 'Change Test Points', command = lambda: master.switch_frame(ChangeTestPage))
		collectOEButton = ttk.Button(self, text = ' Collect OE Data', command = lambda: master.switch_frame(CollectOEDataPage))
		checkDatabaseButton = ttk.Button(self, text = 'Check Database', command = lambda: master.switch_frame(CheckDatabasePage))

		# Setup weights

		# Place widgets
		checkComButton.grid(sticky = 'EW')
		calibrationButton.grid(sticky = 'EW')
		changeTestButton.grid(sticky = 'EW')
		collectOEButton.grid(sticky = 'EW')
		checkDatabaseButton.grid(sticky = 'EW')

		Button(self, text = "Go Back", command = lambda: master.switch_frame(AdminPage)).grid() # Test button


class ComPage(Frame):
	def __init__(self, master):				 		# Initialize ComPage (Frame within window)
		Frame.__init__(self, master)
		self.ports = ['List of COM ports in use:']	# Array of COM ports
		self.labelOut = StringVar()			 		# What will be displayed

		# Setup widgets
		comLabel = Label(self, textvariable = self.labelOut, font = 18)
		changeButton = ttk.Button(self, text = 'Open Config File', command = lambda: self.openConfig())
		
		# Setup weights

		# Place widgets
		comLabel.grid(row = 0)
		changeButton.grid(row = 1)

		Button(self, text = "Go Back", command = lambda: master.switch_frame(MaintenancePage)).grid(row = 2) # Test button   

		self.checkCom() 

	def checkCom(self):
		for port in serial.tools.list_ports.comports():	 	# List all COM ports
			self.ports.append(str(port))   
		self.labelOut.set('\n'.join(self.ports))			# Display on label

	def openConfig(self):
		subprocess.Popen(['C:\\Windows\\notepad.exe', 'config.py'])


class CalibrationPage(Frame):
	def __init__(self, master):				 # Initialize CalibrationPage (Frame within window)
		Frame.__init__(self, master)

		# Setup widgets

		# Setup weights

		# Place widgets

		Label(self, text = 'This is calibration page').grid()
		Button(self, text = "Go Back", command = lambda: master.switch_frame(MaintenancePage)).grid(row = 1) # Test button


class ChangeTestPage(Frame):
	def __init__(self, master):				 # Initialize ChangeTestPage (Frame within window)
		Frame.__init__(self, master)

		# Setup widgets

		# Setup weights

		# Place widgets

		Label(self, text = 'This is changeTest page').grid()
		Button(self, text = "Go Back", command = lambda: master.switch_frame(MaintenancePage)).grid(row = 1) # Test button


class CollectOEDataPage(Frame):		#!
	def __init__(self, master):				 # Initialize CollectOEDataPage (Frame within window)
		Frame.__init__(self, master)
		self.grid(padx = 10, sticky = 'E')
		self.path = '/Users/co_engineering/Desktop/Data/'		#! Path to where you want data file

		# Setup widgets
			# Entry
		self.entryFrame = Frame(self, bg = 'blue')
		self.entryLabel = Label(self.entryFrame, text = 'Sensor Name', bg = '#006FFF', font = ('Arial', 20), fg = 'white',  relief = RAISED)
		self.nameForm = Entry(self.entryFrame, font = ('Arial 20'), width = 15)
		self.nameForm.focus()

			# Buttons
		self.buttonFrame = Frame(self, bg = 'blue')
		self.startVacuumButton = Button(self.buttonFrame,text= 'Start Vacuum\nTest', bg = 'Green', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 12, state = NORMAL, command = lambda: self.vacuumTestStart(master))
		self.startPressure1Button = Button(self.buttonFrame,text= 'Start Pressure\n1 Bar Test', bg = 'Green', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 12, state = NORMAL, command = lambda: self.pressureTestStart(master, 14.5))
		self.startPressure2Button = Button(self.buttonFrame,text= 'Start Pressure\n2 Bar Test', bg = 'Green', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 12, state = NORMAL, command = lambda: self.pressureTestStart(master, 29))
		self.startPressure3Button = Button(self.buttonFrame,text= 'Start Pressure\n3 Bar Test', bg = 'Green', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 12, state = NORMAL, command = lambda: self.pressureTestStart(master, 43.5))
		self.startPressure4Button = Button(self.buttonFrame,text= 'Start Pressure\n4 Bar Test', bg = 'Green', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 12, state = NORMAL, command = lambda: self.pressureTestStart(master, 58))
		self.stopButton = Button(self.buttonFrame, text = 'Stop Test', bg = 'Red', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 12, state = DISABLED, command = lambda: self.testEnd(master))

			# Label
		self.pressureWarning = Label(self, text = 'WARNING:\nPressurized\nDo Not\nRemove', bg = 'orange', font = ('Arial', 20, 'bold'), relief = RAISED)
			
			# Graph
		self.dataOutput = tkst.ScrolledText(self, width = 60)
		style.use("ggplot")
		self.f = plt.figure(figsize=(5,4), dpi=100)
		self.a = self.f.add_subplot(111)
		self.a.set_xlabel('Pressure (PSIA)')
		self.a.set_ylabel('Voltage')
		self.graph = FigureCanvasTkAgg(self.f, self)
		self.graph.draw()

		# Place widgets
		self.dataOutput.grid(row = 0, column = 1, rowspan = 2, padx = 10, pady = 10)
		self.graph.get_tk_widget().grid(row = 2, column = 1, rowspan = 2, padx = 10, pady = 10)
		self.entryFrame.grid(row = 0, column = 2)
		self.entryLabel.grid(row = 0, column = 0)
		self.nameForm.grid(row = 0, column = 1)
		self.buttonFrame.grid(row = 1, column = 2, rowspan = 3)
		self.startVacuumButton.grid(row = 0, column = 0, padx = 10, pady = 5)
		self.startPressure1Button.grid(row = 1, column = 0, padx = 10, pady = 5)
		self.startPressure2Button.grid(row = 2, column = 0, padx = 10, pady = 5)
		self.startPressure3Button.grid(row = 3, column = 0, padx = 10, pady = 5)
		self.startPressure4Button.grid(row = 4, column = 0, padx = 10, pady = 5)
		self.stopButton.grid(row = 5, column = 0, padx = 10, pady = 5)

	def sealCheck(self, master, currentPressure, startPressure):	# Checks pressure to make sure sensor is sealed, used with after()
		if abs(currentPressure - startPressure) < 1:
			self.estop = True
			self.testEnd(master)
			messagebox.showerror('Error', 'Sensor Not Sealed, Aborting Test')

	def vacuumTestStart(self, master):
		vacuumTestPressure = -10	# PSI
		xList = []	  				# Pressure x axis
		yList = []	  				# Resistance y axis
		self.estop = False			# Emergency stop flag
		
		master.transStatus = 1
		master.dutStatus = 1

		self.startVacuumButton.config(state = DISABLED)
		self.startPressure1Button.config(state = DISABLED)
		self.startPressure2Button.config(state = DISABLED)
		self.startPressure3Button.config(state = DISABLED)
		self.startPressure4Button.config(state = DISABLED)
		self.stopButton.config(state = NORMAL)

		today = str(datetime.date.today())
		if self.nameForm.get() == '':						# If no name given
			fileName = (today + '_vacuum.csv')				# Call it today's date + file extension
		else:
			fileName = (today + '_' + self.nameForm.get() + '_vacuum.csv') # Grabbing the value from the entry and adding the file extension

		self.data = open(self.path + fileName,'a')					# Make/Open File
		self.outd(fileName + ' opened . . . \n')
		master.fileStatusLabel.config(text = ' ↻ ', bg = '#cccc00')	# Change file status label

		### Start vacuum test
		self.outd('Starting Vacuum Test . . . \n')
		message = '8,0,0,|'
		master.arduino.write(message.encode())
		time.sleep(.1)
		message = '9,0,0,|'
		master.arduino.write(message.encode())
		time.sleep(.1)

		### Take readings
		self.outd('\nPSIA....Voltage\n\n')
		self.data.write('PSIA,Voltage\n')			# Print headers
		startPressure = 0
		while startPressure == 0:
			startPressure = round(master.transValue * 14.504, 3)
		currentPressure = startPressure
		currentDut = round(master.dutValue, 3)
		self.outd('Start Pressure: {}\n'.format(str(startPressure)))
		self.after(5000, lambda: self.sealCheck(master, currentPressure, startPressure))
		while (currentPressure - startPressure) > vacuumTestPressure:	# Vacuum until test pressure reached
			currentPressure = round(master.transValue * 14.504, 3)		# PSI
			currentDut = round(master.dutValue, 3)
			if self.estop:
				return	
			message = '11,' + str(currentPressure) + ',' + str(currentDut) + ',|'
			master.arduino.write(message.encode())									# Output to stand displays
			self.outd('')															# Update screen
			time.sleep(.01)
		message = '10,' + str(currentPressure) + ',' + str(currentDut) + ',|'
		master.arduino.write(message.encode())
		time.sleep(1)
		currentPressure = round(master.transValue * 14.504, 3)						# PSI
		currentDut = round(master.dutValue, 3)
		try:
			self.data.write(str(currentPressure) + ',' + str(currentDut) + '\n')  	# Output to file
		except:
			return
		self.outd(str(currentPressure) + '	' + str(currentDut) + '\n')				# Output to screen
		xList.append(currentPressure)
		yList.append(currentDut)
		self.a.clear()																# Clear old graph
		self.a.set_xlabel('Pressure (PSI)')
		self.a.set_ylabel('Voltage')
		self.a.plot(xList, yList)													# Draw new graph 
		self.graph.draw()

		point = currentPressure - (vacuumTestPressure / 5)
		while point < startPressure - 1:								# Take 7 readings
			while currentPressure < point:
				currentPressure = round(master.transValue * 14.504, 3)	# PSI
				currentDut = round(master.dutValue, 3)	
				message = '2,' + str(currentPressure) + ',' + str(currentDut) + ',|'
				master.arduino.write(message.encode())
				self.outd('')											# Update screen
				time.sleep(.01)
			message = '10,' + str(currentPressure) + ',' + str(currentDut) + ',|'
			master.arduino.write(message.encode())
			time.sleep(1)
			currentPressure = round(master.transValue * 14.504, 3)		# PSI
			currentDut = round(master.dutValue, 3)
			try:
				self.data.write(str(currentPressure) + ',' + str(currentDut) + '\n')  	# Output to file
			except:
				return
			self.outd(str(currentPressure) + '	' + str(currentDut) + '\n')				# Output to screen
			xList.append(currentPressure)
			yList.append(currentDut)
			self.a.clear()												# Clear old graph
			self.a.set_xlabel('Pressure (PSI)')
			self.a.set_ylabel('Voltage')
			self.a.plot(xList, yList)									# Draw new graph 
			self.graph.draw()
			point = point - (vacuumTestPressure / 6)
			
		message = '2,' + str(currentPressure) + ',' + str(currentDut) + ',|'
		master.arduino.write(message.encode())
		self.outd('')													# Update screen
		time.sleep(3)
		currentPressure = round(master.transValue * 14.504, 3)			# PSI
		currentDut = round(master.dutValue, 3)
		try:
			self.data.write(str(currentPressure) + ',' + str(currentDut) + '\n')  	# Output to file
		except:
			return
		self.outd(str(currentPressure) + '	' + str(currentDut) + '\n')				# Output to screen
		xList.append(currentPressure)
		yList.append(currentDut)
		self.a.clear()				# Clear old graph
		self.a.set_xlabel('Pressure (PSI)')
		self.a.set_ylabel('Voltage')
		self.a.plot(xList, yList)	# Draw new graph 
		self.graph.draw()
		
		### Empty rig
		self.testEnd(master)

	def continuousVacuumTestStart(self, master):	# Currently not in use
		vacuumTestPressure = -10	# PSI
		xList = []	 				# Pressure x axis
		yList = []	 				# Resistance y axis
		
		master.transStatus = 1
		master.dutStatus = 1

		self.startVacuumButton.config(state = DISABLED)
		self.startPressure1Button.config(state = DISABLED)
		self.startPressure2Button.config(state = DISABLED)
		self.startPressure3Button.config(state = DISABLED)
		self.startPressure4Button.config(state = DISABLED)
		self.stopButton.config(state = NORMAL)

		today = str(datetime.date.today())
		if self.nameForm.get() == '':								# If no name given
			fileName = (today + '_continuous.csv')					# Call it today's date + file extension
		else:
			fileName = (today + '_' + self.nameForm.get() + '_continuous.csv') # Grabbing the value from the entry and adding the file extension

		self.data = open(self.path + fileName,'a')					# Make/Open File
		self.outd(fileName + ' opened . . . \n')
		master.fileStatusLabel.config(text = ' ↻ ', bg = '#cccc00')	# Change file status label

		### Start vacuum test
		self.outd('Starting Vacuum Test . . . \n')
		message = '8,0,0,|'
		master.arduino.write(message.encode())
		time.sleep(.1)
		message = '9,0,0,|'
		master.arduino.write(message.encode())
		time.sleep(.1)

		### Take readings 
		self.outd('\nPSIA....Voltage\n\n')
		self.data.write('PSIA,Voltage\n')						# Print headers
		while master.transValue == 0 or master.dutValue == 0:
			pass												# Make sure a valid value is read in
		startPressure = round(master.transValue * 14.504, 3)	# PSI
		currentPressure = startPressure							# PSI
		currentDut = round(master.dutValue, 3)		
		while (currentPressure - startPressure) > vacuumTestPressure:
			currentPressure = round(master.transValue * 14.504, 3)	# PSI
			currentDut = round(master.dutValue, 3)	
			try:	
				self.data.write(str(currentPressure) + ',' + str(currentDut) + '\n')# Output to file
			except:
				return
			message = '11,' + str(currentPressure) + ',' + str(currentDut) + ',|'
			master.arduino.write(message.encode())									# Output to stand displays
			self.outd(str(currentPressure) + '	' + str(currentDut) + '\n')			# Output to screen
			xList.append(currentPressure)
			yList.append(currentDut)
			self.a.clear()				# Clear old graph
			self.a.set_xlabel('Pressure (PSI)')
			self.a.set_ylabel('Voltage')
			self.a.plot(xList, yList)	# Draw new graph 
			self.graph.draw()
			time.sleep(.3)

		### Empty rig
		self.testEnd(master)

	def pressureTestStart(self, master, pressure):
		pressureTestPressure = pressure	# PSI	
		xList = []	  					# Pressure x axis
		yList = []	  					# Resistance y axis
		self.estop = False				# Emergency stop flag
		
		master.transStatus = 1
		master.dutStatus = 1

		self.startVacuumButton.config(state = DISABLED)
		self.startPressure1Button.config(state = DISABLED)
		self.startPressure2Button.config(state = DISABLED)
		self.startPressure3Button.config(state = DISABLED)
		self.startPressure4Button.config(state = DISABLED)
		self.stopButton.config(state = NORMAL)
		self.pressureWarning.grid(row = 1, column = 0)

		today = str(datetime.date.today())
		if self.nameForm.get() == '':								# If no name given
			fileName = (today + '_pressure.csv')					# Call it today's date + file extension
		else:
			fileName = (today + '_' + self.nameForm.get() + '_pressure.csv') # Grabbing the value from the entry and adding the file extension

		self.data = open(self.path + fileName,'a')					# Make/Open File
		self.outd(fileName + ' opened . . . \n')
		master.fileStatusLabel.config(text = ' ↻ ', bg = '#cccc00')	# Change file status label

		### Start pressure test
		self.outd('Starting pressure Test . . .\n')
		message = '8,0,0,|'
		master.arduino.write(message.encode())
		time.sleep(.1)
		message = '12,0,0,|'
		master.arduino.write(message.encode())
		time.sleep(.1)

		### Take readings
		self.outd('\nPSIA....Voltage\n\n')
		self.data.write('PSIA,Voltage\n')							# Print headers
		startPressure = 0
		while startPressure == 0:
			startPressure = round(master.transValue * 14.504, 3)
		currentPressure = startPressure
		currentDut = round(master.dutValue, 3)
		self.outd('Start Pressure: {}\n'.format(str(startPressure)))
		self.after(5000, lambda: self.sealCheck(master, currentPressure, startPressure))
		while (currentPressure - startPressure) < pressureTestPressure:	# Pressurize stand
			currentPressure = round(master.transValue * 14.504, 3)	# PSI
			currentDut = round(master.dutValue, 3)
			if self.estop:
				return	
			message = '12,' + str(currentPressure) + ',' + str(currentDut) + ',|'
			master.arduino.write(message.encode())					# Output to stand displays
			self.outd('')											# Update screen
			time.sleep(.01)
		message = '8,' + str(currentPressure) + ',' + str(currentDut) + ',|'
		master.arduino.write(message.encode())
		time.sleep(1)
		currentPressure = round(master.transValue * 14.504, 3)		# PSI
		currentDut = round(master.dutValue, 3)
		try:
			self.data.write(str(currentPressure) + ',' + str(currentDut) + '\n')  	# Output to file
		except:
			return
		self.outd(str(currentPressure) + '	' + str(currentDut) + '\n')				# Output to screen
		xList.append(currentPressure)
		yList.append(currentDut)
		self.a.clear()				# Clear old graph
		self.a.set_xlabel('Pressure (PSI)')
		self.a.set_ylabel('Voltage')
		self.a.plot(xList, yList)	# Draw new graph 
		self.graph.draw()

		point = currentPressure - (pressureTestPressure / 5)
		while point > startPressure + 1:								# Take 7 readings
			while currentPressure > point:
				currentPressure = round(master.transValue * 14.504, 3)	# PSI
				currentDut = round(master.dutValue, 3)	
				message = '0,' + str(currentPressure) + ',' + str(currentDut) + ',|'
				master.arduino.write(message.encode())
				self.outd('')											# Update screen
				time.sleep(.01)
			message = '8,' + str(currentPressure) + ',' + str(currentDut) + ',|'
			master.arduino.write(message.encode())
			time.sleep(1)
			currentPressure = round(master.transValue * 14.504, 3)		# PSI
			currentDut = round(master.dutValue, 3)
			try:
				self.data.write(str(currentPressure) + ',' + str(currentDut) + '\n')  	# Output to file
			except:
				return
			self.outd(str(currentPressure) + '	' + str(currentDut) + '\n')				# Output to screen
			xList.append(currentPressure)
			yList.append(currentDut)
			self.a.clear()				# Clear old graph
			self.a.set_xlabel('Pressure (PSI)')
			self.a.set_ylabel('Voltage')
			self.a.plot(xList, yList)	# Draw new graph 
			self.graph.draw()
			point = point - (pressureTestPressure / 6)
			
		message = '0,' + str(currentPressure) + ',' + str(currentDut) + ',|'
		master.arduino.write(message.encode())
		self.outd('')												# Update screen
		time.sleep(3)
		currentPressure = round(master.transValue * 14.504, 3)		# PSI
		currentDut = round(master.dutValue, 3)
		try:
			self.data.write(str(currentPressure) + ',' + str(currentDut) + '\n')  	# Output to file
		except:
			return
		self.outd(str(currentPressure) + '	' + str(currentDut) + '\n')				# Output to screen
		xList.append(currentPressure)
		yList.append(currentDut)
		self.a.clear()				# Clear old graph
		self.a.set_xlabel('Pressure (PSI)')
		self.a.set_ylabel('Voltage')
		self.a.plot(xList, yList)	# Draw new graph 
		self.graph.draw()
		
		### Empty rig
		self.testEnd(master)

	def continuousPressureTestStart(self, master, pressure):	# Currently not in use
		pressureTestPressure = pressure	# PSI	
		xList = []	  					# Pressure x axis
		yList = []	  					# Resistance y axis
		
		master.transStatus = 1
		master.dutStatus = 1

		self.startVacuumButton.config(state = DISABLED)
		self.startPressure1Button.config(state = DISABLED)
		self.startPressure2Button.config(state = DISABLED)
		self.startPressure3Button.config(state = DISABLED)
		self.startPressure4Button.config(state = DISABLED)
		self.stopButton.config(state = NORMAL)
		self.pressureWarning.grid(row = 1, column = 0)

		today = str(datetime.date.today())
		if self.nameForm.get() == '':								# If no name given
			fileName = (today + '_pressure.csv')					# Call it today's date + file extension
		else:
			fileName = (today + '_' + self.nameForm.get() + '_pressure.csv') # Grabbing the value from the entry and adding the file extension

		self.data = open(self.path + fileName,'a')					# Make/Open File
		self.outd(fileName + ' opened . . . \n')
		master.fileStatusLabel.config(text = ' ↻ ', bg = '#cccc00')	# Change file status label

		### Start pressure test
		self.outd('Starting pressure Test . . .\n')
		self.outd('\nPSIA....Voltage\n\n')
		self.data.write('PSIA,Voltage\n')			# Print headers
		currentPressure = round(master.transValue * 14.504, 3)
		currentDut = round(master.dutValue, 3)
		message = '10,' + str(currentPressure) + ',' + str(currentDut) + ',|'
		master.arduino.write(message.encode())
		time.sleep(.1)
		message = '14,' + str(currentPressure) + ',' + str(currentDut) + ',|'
		master.arduino.write(message.encode())
		time.sleep(.1)

		### Take readings
		startPressure = master.transValue * 14.504	# PSI
		currentPressure = round(startPressure, 3)	# PSI
		currentDut = round(master.dutValue, 3)		
		while (currentPressure - startPressure) < pressureTestPressure:
			currentPressure = round(master.transValue * 14.504, 3)	# PSI
			currentDut = round(master.dutValue, 3)
			try:					
				self.data.write(str(currentPressure) + ',' + str(currentDut) + '\n')  	# Output to file
			except:
				return
			message = '14,' + str(currentPressure) + ',' + str(currentDut) + ',|'
			master.arduino.write(message.encode())									# Output to stand displays
			self.outd(str(currentPressure) + '	' + str(currentDut) + '\n')	   		# Output to screen
			xList.append(currentPressure)
			yList.append(currentDut)
			self.a.clear()				# Clear old graph
			self.a.set_xlabel('Pressure (PSI)')
			self.a.set_ylabel('Voltage')
			self.a.plot(xList, yList)	# Draw new graph 
			self.graph.draw()
			time.sleep(.1)

		### Empty rig
		self.outd('Releasing Pressure . . .\n')
		message = '10,' + str(currentPressure) + ',' + str(currentDut) + ',|'
		master.arduino.write(message.encode())
		time.sleep(.1)
		message = '2,' + str(currentPressure) + ',' + str(currentDut) + ',|'
		master.arduino.write(message.encode())
		time.sleep(3)
		self.testEnd(master)

	def testEnd(self, master):
		self.startVacuumButton.config(state = NORMAL)
		self.startPressure1Button.config(state = NORMAL)
		self.startPressure2Button.config(state = NORMAL)
		self.startPressure3Button.config(state = NORMAL)
		self.startPressure4Button.config(state = NORMAL)
		self.stopButton.config(state = DISABLED)
		self.pressureWarning.grid_forget()

		master.transStatus = 2
		master.dutStatus = 2
		self.estop = True

		message = '0,0,0,|'
		master.arduino.write(message.encode())
		self.outd('Test done . . . \n\n\n')

		self.data.close()
		master.fileStatusLabel.config(text = '✓', bg = 'green')	# Change file status label

	def outd(self,x):				# Output to dataOutput
		self.dataOutput.insert(END, x)
		self.dataOutput.see(END)	# Scroll to bottom
		self.update()


class CheckDatabasePage(Frame):
	def __init__(self, master):				 # Initialize CheckDatabasePage (Frame within window)
		Frame.__init__(self, master)

		# Setup widgets

		# Setup weights

		# Place widgets

		Label(self, text = 'This is checkDatabase page').grid()
		Button(self, text = "Go Back", command = lambda: master.switch_frame(MaintenancePage)).grid(row = 1) # Test button


def onClosing():
	if messagebox.askokcancel('Quit', 'Do you want to quit?'):	# This is a confirmation of wanting to quit the program	
		app.commShutdown()
		app.destroy()											# Close the prgram
		sys.exit()

if __name__ == "__main__":
	app = Program()				# Run the class
	app.title ("MAP Tester")	# Name of window
	app.mainloop()				# Start the program and keep is running
