import sys
from collections import deque

n, x = [int(x) for x in sys.stdin.readline().split()]
b = [int(x) for x in sys.stdin.readline().split()]


b.sort()

b = deque(b)


def swap(x1):
    aux = b.pop()
    b.insert(x1, aux)


def swapleft(x1):
    aux = b.popleft()
    b.insert(x1, aux)


fail = False

for i in range(n-1):
    if b[i] + b[i+1] == x:
        if b[i+1] != b[-1]:
            swap(i+1)
        elif b[i] != b[0]:
            swapleft(i)
        else:
            sys.stdout.write("*\n")
            fail = True
            break

if not fail:
    for c in range(len(b)-1):
        sys.stdout.write(str(b[c])+' ')
    sys.stdout.write(str(b[-1])+'\n')
