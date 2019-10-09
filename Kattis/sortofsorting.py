import sys

def sorting():
    cin = -1
    while not cin == 0:
        cin = int(input())
        names = [input() for i in range(cin)]
        names.sort(key = getTwo)
        for i in range(len(names)):
            print(names[i])
        print()

def getTwo(x):
    return x[0:2]

def testGetTwo():
    assert getTwo('Chase') == 'Ch'
    assert getTwo('zZzZzZz') == 'zZ'

if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == 'test':
        testGetTwo()
    else:
        sorting()
        