import sys

n = int(sys.stdin.readline())
inp = [int(x) for x in sys.stdin.readline().split()]

consec = 0
punt = 0

for v in inp:
    if v == 1:
        punt += 1
        consec += 1
        if consec >= 3:
            punt += 1
    if v == 0:
        punt -= 1
        consec = 0

print(punt)
