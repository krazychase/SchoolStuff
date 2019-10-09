import sys

def different():
    data = sys.stdin.readlines()
    for i in range(len(data)):
        equation = data[i].split()
        print(abs(int(equation[0])-int(equation[1])))

if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == 'test':
        pass
    else:
        different()