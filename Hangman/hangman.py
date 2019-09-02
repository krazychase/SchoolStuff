# Chase Brown
# Hangman Game
# Due Sept 20

import sys
import time
import random

def play(words):

    word = random.choice(words)

    printTitle()
    fails = 6 
    printGallow(fails, word)

    print(word)

def printTitle():
    print(' _   _ ')
    time.sleep(.1)                                        
    print('| | | |')
    time.sleep(.1)                                        
    print('| |_| | __ _ _ __   __ _ _ __ ___   __ _ _ __')
    time.sleep(.1)  
    print('|  _  |/ _` |  _ \ / _` | \'_ ` _ \ / _` | \'_ \\') 
    time.sleep(.1)
    print('| | | | (_| | | | | (_| | | | | | | (_| | | | |')
    time.sleep(.1)
    print('\_| |_/\__,_|_| |_|\__, |_| |_| |_|\__,_|_| |_|')
    time.sleep(.1)
    print('                    __/ |')            
    time.sleep(.1)          
    print('                   |___/')
    time.sleep(1)

def printGallow(fails, word):
    if fails == 0:
        print('_______________________ ')
        print('| _____________________|')
        print('| |  /      | |         ')
        print('| | /       (_)         ')
        print('| |/                    ')
        print('| |                     ')
        print('| |                     ')
        print('| |                     ')
        print('| |                     ')
        print('| |_____________________')
        print('|                       |')
        print('|_______________________|')
    elif fails == 1:
        print('_______________________ ')
        print('| _____________________|')
        print('| |  /      | |         ')
        print('| | /      ( ツ )         ')
        print('| |/                    ')
        print('| |                     ')
        print('| |                     ')
        print('| |                     ')
        print('| |                     ')
        print('| |_____________________')
        print('|                       |')
        print('|_______________________|')
    elif fails == 2:
        print('_______________________ ')
        print('| _____________________|')
        print('| |  /      | |         ')
        print('| | /      ( ツ )         ')
        print('| |/         |           ')
        print('| |          |           ')
        print('| |          |           ')
        print('| |                     ')
        print('| |                     ')
        print('| |_____________________')
        print('|                       |')
        print('|_______________________|')
    elif fails == 3:
        print('_______________________ ')
        print('| _____________________|')
        print('| |  /      | |         ')
        print('| | /      ( ツ )         ')
        print('| |/         |           ')
        print('| |         /|           ')
        print('| |        / |           ')
        print('| |                     ')
        print('| |                     ')
        print('| |_____________________')
        print('|                       |')
        print('|_______________________|')        
    elif fails == 4:
        print('_______________________ ')
        print('| _____________________|')
        print('| |  /      | |         ')
        print('| | /      ( ツ )         ')
        print('| |/         |           ')
        print('| |         /|\           ')
        print('| |        / | \         ')
        print('| |                     ')
        print('| |                     ')
        print('| |_____________________')
        print('|                       |')
        print('|_______________________|')        
    elif fails == 5:
        print('_______________________ ')
        print('| _____________________|')
        print('| |  /      | |         ')
        print('| | /      ( ツ )         ')
        print('| |/         |           ')
        print('| |         /|\           ')
        print('| |        / | \         ')
        print('| |         /           ')
        print('| |        /             ')
        print('| |_____________________')
        print('|                       |')
        print('|_______________________|')        
    elif fails == 6:
        print('_______________________ ')
        print('| _____________________|')
        print('| |  /      | |         ')
        print('| | /      ( ツ )         ')
        print('| |/         |           ')
        print('| |         /|\           ')
        print('| |        / | \         ')
        print('| |         / \          ')
        print('| |        /   \          ')
        print('| |_____________________')
        print('|                       |')
        print('|_______________________|')
        print('\n' + word)
        print(' _____   ___  ___  ___ _____ _____  _   _ ___________ ')
        time.sleep(.1)
        print('|  __ \ / _ \ |  \/  ||  ___|  _  || | | |  ___| ___ \\')
        time.sleep(.1)
        print('| |  \// /_\ \| .  . || |__ | | | || | | | |__ | |_/ /')
        time.sleep(.1)
        print('| | __ |  _  || |\/| ||  __|| | | || | | |  __||    / ')
        time.sleep(.1)
        print('| |_\ \| | | || |  | || |___\ \_/ /\ \_/ / |___| |\ \ ')
        time.sleep(.1)
        print(' \____/\_| |_/\_|  |_/\____/ \___/  \___/\____/\_| \_|') 
        time.sleep(1)
        playAgain(words)       
       
def playAgain(words):
    answer = input('Play Again? (Y/N) ')
    if answer.upper() == 'Y':
        play(words)
    else:
        sys.exit()

if __name__ == '__main__':
    
    words = []
    dictionary = open('Hangman\dictionary.txt', 'r') 
    for i in dictionary:
        words.append(i.upper())
    
    play(words)