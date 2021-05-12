'''
Application that predicts Iris species given features using AI
Chase Brown
'''

# from keras.models import load_model		# Loading dnn
from pathlib import Path					# Cross platform pathing
import pickle								# Loading trained models
from sklearn.datasets import load_iris		# Iris dataset
from tkinter import *						# GUI
import tkinter.ttk as ttk		   			# Themed GUI
from tkinter import messagebox				# Pop Up Windows

class Program(Tk):
	def __init__ (self):
		Tk.__init__(self)
		self._frame = None

		# Window Setup
		self.title('Iris Identifier')
		self.configure(background = 'blue')
		self.wm_state('zoomed')

		# Setup widgets
		titleLabel = Label(self, text = ' Iris Identifier ', background = '#006FFF', font = ('Arial', 48, 'bold'), fg = 'white', relief = RAISED)

		# Setup weights
		self.columnconfigure(0, weight = 1)
		self.columnconfigure(1, weight = 1)
		self.rowconfigure(1, weight = 1)

		# Place widgets
		titleLabel.grid(row = 0, column = 1, padx = 10, pady = 10, sticky = 'NE')
		self.switch_frame(MainPage)				# Switch to MainPage

	def switch_frame(self, frame_class):		# Destroys current frame, replaces with new
		new_frame = frame_class(self)
		if self._frame is not None:
			self._frame.destroy()
		self._frame = new_frame
		self._frame.grid(row = 1, column = 0, columnspan = 2)
		self._frame.config(background = 'blue')


class MainPage(Frame):
	def __init__(self, master):
		Frame.__init__(self, master)

		# Setup widgets
		slLabel = Label(self,text = 'Sepal Length (cm):', bg = '#006FFF', font = ('Arial', 20), fg = 'white',  relief = RAISED)
		swLabel = Label(self,text = 'Sepal Width (cm):', bg = '#006FFF', font = ('Arial', 20), fg = 'white',  relief = RAISED)
		plLabel = Label(self,text = 'Pedal Length (cm):', bg = '#006FFF', font = ('Arial', 20), fg = 'white',  relief = RAISED)
		pwLabel = Label(self,text = 'Pedal Width (cm):', bg = '#006FFF', font = ('Arial', 20), fg = 'white',  relief = RAISED)
		speciesLabel = Label(self,text = 'Species:', bg = '#006FFF', font = ('Arial', 20), fg = 'white',  relief = RAISED)
		self.slForm = Entry(self, font = ('Arial 20'), width = 12)
		self.swForm = Entry(self, font = ('Arial 20'), width = 12)
		self.plForm = Entry(self, font = ('Arial 20'), width = 12)
		self.pwForm = Entry(self, font = ('Arial 20'), width = 12)
		self.speciesForm = Entry(self, font = ('Arial 20'), width = 12)
		testButton = Button(self, text = 'Identify', font = ('Microsoft Sans Serif', 20, 'bold'), height = 3, width = 10, command = lambda: self.identify())

		# Setup weights
		self.columnconfigure(0, weight = 1)
		self.columnconfigure(1, weight = 1)
		self.rowconfigure(0, weight = 1)
		self.rowconfigure(1, weight = 1)

		# Place widgets
		slLabel.grid(row = 0,column = 0, pady = 10, sticky = 'EW')
		swLabel.grid(row = 1,column = 0, pady = 10, sticky = 'EW')
		plLabel.grid(row = 2,column = 0, pady = 10, sticky = 'EW')
		pwLabel.grid(row = 3,column = 0, pady = 10, sticky = 'EW')
		self.slForm.grid(row = 0, column = 1)
		self.swForm.grid(row = 1, column = 1)
		self.plForm.grid(row = 2, column = 1)
		self.pwForm.grid(row = 3, column = 1)
		testButton.grid(row = 4, column = 1, padx = 10, sticky = 'NSEW')
		speciesLabel.grid(row = 0, column = 2, rowspan = 2, pady = 10, sticky = 'EW')
		self.speciesForm.grid(row = 0, column = 3, rowspan = 2, pady = 10, sticky = 'EW')

		### Load trained models
		self.dataset = load_iris()
		# self.knn = pickle.load(open(Path('iris/models/knn.sav') , 'rb'))
		# self.naive_bayes = pickle.load(open(Path('iris/models/naive_bayes.sav') , 'rb'))
		# self.logit = pickle.load(open(Path('iris/models/logit.sav') , 'rb'))
		# self.svm = pickle.load(open(Path('iris/models/svm.sav') , 'rb'))
		# self.decision_tree = pickle.load(open(Path('iris/models/decision_tree.sav') , 'rb'))
		# self.random_forest = pickle.load(open(Path('iris/models/random_forest.sav') , 'rb'))
		self.mlp = pickle.load(open(Path('iris/models/mlp.sav') , 'rb'))		# Using mlp since it is the only model to have 100% accuracy in tests
		# self.dnn = load_model(Pth('iris/models/dnn'))

	def identify(self):
		sl = self.slForm.get()
		sw = self.swForm.get()
		pl = self.plForm.get()
		pw = self.pwForm.get()

		if not (sl and sw and pl and pw):
			messagebox.showerror('Error', 'Please enter all info')
			return

		self.speciesForm.delete(0,END)
		iris = [[sl,sw,pl,pw]]
		prediction = self.mlp.predict(iris)
		species = self.dataset['target_names'][prediction][0]
		self.speciesForm.insert(0, species)



if __name__ == "__main__":
	app = Program()				# Init the class
	app.mainloop()				# Start the program and keep is running
