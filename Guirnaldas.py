import sys

s = sys.stdin.readline()

p = 0
t = 0
u = 0
a = 0

for c in s:
    if c == 'P':
        p += 1
    if c == 'T':
        t += 1
    if c == 'U':
        u += 1
    if c == 'A':
        a += 1

taps = min(t, a, p)
t -= taps
p -= taps

tups = min(t, u, p)

print(taps + tups)
