# Chase Brown
# Hangman Game
import time

def play(words):

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
    time.sleep(.1)

if __name__ == '__main__':
    
    words = []
    dictionary = open('dictionary.txt', 'r') 
    for x in dictionary:
        words.append(x)
    
    play(words)

    print(words)