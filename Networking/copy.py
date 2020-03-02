# Chase Brown
# Copy a file 

import sys

def copy(src, dest):
    with open(src,'rb') as source, open(dest,'wb') as destination:
        done = False
        while not done:
            buf = source.read(4096)     # Read 4 kB at a time for speed
            if buf: 
                destination.write(buf)
            else:
                done = True

if __name__ == "__main__":
    if len(sys.argv) > 1:
        copy(sys.argv[1], sys.argv[2])
    else:   
        src = input('Source file: ')
        dest = input('Destination file: ')
        copy(src, dest)