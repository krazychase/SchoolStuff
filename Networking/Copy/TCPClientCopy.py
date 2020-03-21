# Chase Brown
# Client side copy file (sending)

import socket
import sys

def copy(src):
    TCP_IP = '127.0.0.1'
    TCP_PORT = 5005
    BUFFER_SIZE = 4096

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((TCP_IP, TCP_PORT))

    with open(src,'rb') as source:
        done = False
        while not done:
            buf = source.read(BUFFER_SIZE)
            s.send(buf)


        data = s.recv(BUFFER_SIZE)
        s.close()

        print(data.decode())  # comfirmation

if __name__ == "__main__":
    if len(sys.argv) > 1:
        copy(sys.argv[1])
    else:   
        src = input('Source file: ')
        copy(src)