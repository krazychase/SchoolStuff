# ls linux alternate
# Chase Brown

import sys
import os

path = os.getcwd()

def ls():
    for entry in os.scandir(path):
        size = os.stat(entry).st_size
        print('{0:20} {1}B'.format(entry.name, str(size)))

def lsReverse():
    entries = []
    for entry in os.scandir(path):
        entries.insert(0, entry)
    for entry in entries:
        size = os.stat(entry).st_size
        print('{0:20} {1}B'.format(entry.name, str(size)))

def lsRecursive(path):
    for entry in os.scandir(path):
        if entry.is_dir():
            newPath = os.path.join(path, entry)
            lsRecursive(newPath)
        print('{0}'.format(entry.name))

if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == '-R':
        lsReverse()
    elif len(sys.argv) > 1 and sys.argv[1] == '-r':
        lsRecursive(path)
    else:
        ls()
        