import sys

n = int(sys.stdin.readline())

conv = []

for p in range((n//2), 0, -1):
    if n % p == 0:
        valid = True
        for c in conv:
            if c % p == 0:
                valid = False
                break
        if valid:
            conv.append(p)


sys.stdout.write(str(len(conv))+'\n')
for c in conv:
    print("1", c)
