import sys

def vauvau():
    data = sys.stdin.readlines()
    dogs = data[0].split()
    heros = data[1].split()

    for i in range(len(dogs)):
        dogs[i] = int(dogs[i])

    for i in range(len(heros)):
        heros[i] = int(heros[i])

    dog1 = dogs[0] + dogs[1]
    dog2 = dogs[2] + dogs[3]
    attacksP = 0
    attacksM = 0
    attacksG = 0

    if heros[0] % dog1 and heros[0] % dog1 <= dogs[0]:
        attacksP += 1
    if heros[0] % dog2 and heros[0] % dog2 <= dogs[2]:
        attacksP += 1
    print(cout(attacksP))

    if heros[1] % dog1 and heros[1] % dog1 <= dogs[0]:
        attacksM += 1
    if heros[1] % dog2 and heros[1] % dog2 <= dogs[2]:
        attacksM += 1
    print(cout(attacksM))

    if heros[2] % dog1 and heros[2] % dog1 <= dogs[0]:
        attacksG += 1
    if heros[2] % dog2 and heros[2] % dog2 <= dogs[2]:
        attacksG += 1
    print(cout(attacksG))

def cout(x):
    if x == 0:
        ans = 'none'
    elif x == 1:
        ans ='one'
    else:
        ans = 'both'
    return ans

def test():
    assert cout(0) == 'none'
    assert cout(1) == 'one'
    assert cout(10000) == 'both'

if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == 'test':
        test()
    else:
        vauvau()