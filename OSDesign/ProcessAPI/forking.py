# Chpt 5 Process API
# Chase Brown

import os

def forking(x):
    x = 100
    print('Original x:', x) 
    n = os.fork() 
    if n > 0: 
        print('Parent process id: ', os.getpid())
        print('Parent x:', x)
        x = 50
        print('New Parent x:',x)
    else: 
        print('Child process id: ', os.getpid()) 
        print('Child x:', x)
        x = 200
        print('New child x:', x)
    # The variable in the parent and child is the same as the original. 
    # When changed in the parent and child, they remain what they were changed to.

def fileFork():
    n = os.fork() 
    if n > 0: 
        print('Parent process id: ', os.getpid())
        f = open('file.txt','a')
        f.write('Parent here.\n')
    else: 
        print('Child process id: ', os.getpid())
        f = open('file.txt','a')
        f.write('Child here.\n')
    # They can both open the same file at the same time. 
    # They can both write to the file at the same time, but the parent seems to write first.

def raceFork():
    n = os.fork() 
    if n > 0:
        i = 0
        for i in range(1000000):
            i = i + 1   # Random operations to eat up CPU time (technically not a wait())
        print('Goodbye')
    else: 
        print('Hello')

def execFork():
    n = os.fork()
    if n > 0:
        pass
    else:
        os.execl('/bin/ls', '/bin/ls', '.')
    # Other exec are used to search different locations,or process environments

def waitFork():
    n = os.fork()
    if n > 0:
        status = os.wait()  # Returns child's PID and exit status once completed
        print("Parent process ID:", os.getpid()) 
        print("Terminated child's process id:", status[0]) 
        print("Signal number that killed the child process:", status[1]) 
    else : 
        print("Child process ID:", os.getpid()) 
        try:
            status = os.wait()
        except Exception as e:
            print(e)        # Wait in child throws and error, no child processes
        
if __name__ == '__main__':          
    # forking(x)    # Question 1
    # fileFork()    # Question 2
    # raceFork()    # Question 3
    # execFork()    # Question 4
    # waitFork()    # Question 5
    pass