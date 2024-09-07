import sys

n = int(sys.stdin.readline())
v = [int(x) for x in sys.stdin.readline().split()]

v.sort()

a = v[-1]
b = v[0]
c = v[0]

print(a*a+b*b+c*c-a*b-a*c-b*c)
