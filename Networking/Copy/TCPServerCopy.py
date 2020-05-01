# Chase Brown
# Server side copy file (receiving)

import socket
import sys

def copy(dest):
    print('start')
    TCP_IP = '127.0.0.1'
    TCP_PORT = 5005
    BUFFER_SIZE = 4096
    done = False

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((TCP_IP, TCP_PORT))
    s.listen()

    with open(dest,'wb') as destination:
        while not done:
            conn, addr = s.accept()
            data = conn.recv(BUFFER_SIZE)
            if not data: 
                done = True
            destination.write(data)
    conn.send('File copied'.encode())  # comfirmation
    print('File copied')
    conn.close()

if __name__ == "__main__":
    if len(sys.argv) > 1:
        copy(sys.argv[1])
    else:   
        dest = input('Destination file: ')
        copy(dest)