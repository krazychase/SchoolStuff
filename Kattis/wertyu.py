import sys

keyboard = ['`','1','2','3','4','5','6','7','8','9','0','-','=',
            'Q','W','E','R','T','Y','U','I','O','P','[',']','\\',
            'A','S','D','F','G','H','J','K','L',';',"'",
            'Z','X','C','V','B','N','M',',','.','/']

def wertyu(data):
    output = ''
    for i in range(len(data) - 1):
        if data[i] == ' ':
            output = output + ' '
        else:
            for j in range(len(keyboard)):
                if data[i] == keyboard[j]:
                    output = output + keyboard[j - 1]
    print(output)

def test():
    pass

if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == 'test':
        test()
    else:
        data = sys.stdin.readlines()
        for i in range(len(data)):
            wertyu(data[i])