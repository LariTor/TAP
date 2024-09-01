import sys

inp = [int(x) for x in sys.stdin.readline().split()]

inp.sort(reverse=True)

if inp[0] < sum(inp[1:]):
    print('N')
else:
    print('S')
