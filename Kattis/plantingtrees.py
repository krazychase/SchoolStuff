import sys

def plantTrees():
    data = sys.stdin.readlines()
    seedNum = data[0]
    time = data[1].split()
    days = 1

    for i in range(len(time)):  # Convert input strings to int
        time[i] = int(time[i])
    time.sort(reverse= True)

    print(findDays(seedNum, time, days))

def findDays(seedNum, time, days):
    for i in range(int(seedNum)):
        if (time[i] + i) > days:
            days = time[i] + i
    return days + 2


def test():
    assert findDays(1, [1000000], 1) == 1000002
    assert findDays(5, [50, 3, 90, 10, 75], 1) == 92

if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == 'test':
        test()
    else:
        plantTrees()