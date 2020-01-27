# ls linux alternate
# Chase Brown

import sys
import os

path = os.getcwd()

def ls():
    for entry in os.scandir(path):
        size = os.stat(entry).st_size
        print('{0:20} {1}B'.format(entry.name, str(size)))

def lsr():
    entries = []
    for entry in os.scandir(path):
        entries.insert(0, entry)
    for entry in entries:
        size = os.stat(entry).st_size
        print('{0:20} {1}B'.format(entry.name, str(size)))

if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == '-r':
        lsr()
    else:
        ls()
        