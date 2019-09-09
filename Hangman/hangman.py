# Chase Brown
# Hangman Game
# Due Sept 20

import sys      # for exit
import time     # for sleep
import random   # for random choice

def play(words):

    word = random.choice(words)
    fails = 0
    correctGuesses = ''

    printTitle()
    print('_ ' * (len(word) - 1))
    print(word)

    while True:
        guess = input('\nGuess a letter: ').upper()
        if guess in word:
            correctGuesses = correctGuesses + guess
            win = True
            printGallow(fails, word)
            for i in range(len(word) - 1):
                if word[i] not in correctGuesses:
                    win = False
                    print('_ ', end = '')
                else:
                    print(word[i] + ' ', end = '')
            if win == True:
                winner(word)
        else:
            fails += 1
            printGallow(fails, word)

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
        print('| | /       / \         ')
        print('| |/       (___)        ')
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
        print('| | /     ( 0o0 )         ')
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
        print('| | /     ( 0o0 )         ')
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
        print('| | /     ( 0o0 )         ')
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
        print('| | /     ( 0o0 )         ')
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
        print('| | /     ( 0o0 )         ')
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
        print('| | /     ( XoX )         ')
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

def winner(word):
    print('\n' + word)
    print('__   __          _    _ _    ')   
    time.sleep(.1)
    print('\ \ / /         | |  | (_)     ') 
    time.sleep(.1)
    print(' \ V /___  _   _| |  | |_ _ __  ')
    time.sleep(.1)
    print('  \ // _ \| | | | |/\| | | \'_ \ ')
    time.sleep(.1)
    print('  | | (_) | |_| \  /\  / | | | |')
    time.sleep(.1)
    print('  \_/\___/ \__,_|\/  \/|_|_| |_|')
    time.sleep(1)
    playAgain(words)
       
def playAgain(words):
    answer = input('Play Again? (Y/N) ')
    if answer.upper() == 'Y':
        play(words)
    elif answer.upper() == 'N':
        sys.exit()
    else:
        playAgain(words)

if __name__ == '__main__':
    
    words = []
    dictionary = open('dictionary.txt', 'r') 
    for i in dictionary:
        words.append(i.upper())
    
    play(words)
