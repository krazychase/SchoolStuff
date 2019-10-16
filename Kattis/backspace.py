import sys

data = sys.stdin.readline()[::-1]   # read in backwards
output = []
bs = 0
for i in range(len(data)):
    if(data[i] == '<'):
        bs = bs + 1
    elif(bs > 0):   # if backspace, skip next char
        bs = bs - 1
    else:
        output.append(data[i])   # if not, put at beginning of output
print(''.join(output)[::-1])

def backspace(data):
    data = data[::-1]   # read in backwards
    output = []
    bs = 0
    for i in range(len(data)):
        if(data[i] == '<'):
            bs = bs + 1
        elif(bs > 0):   # if backspace, skip next char
            bs = bs - 1
        else:
            output.append(data[i])   # if not, put at beginning of output
    print(''.join(output)[::-1])
    return ''.join(output)[::-1]

if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == 'test':
        data = 'chh<ass<s<ee<'
        assert backspace(data) == 'chase'
        data = '1234567890<<<<<<<<<<'
        assert backspace(data) == ''
        print('Passed')
    else:
        data = sys.stdin.readline()
        backspace(data)