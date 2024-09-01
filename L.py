import sys


def is_pow(x):
    print(x.bit_length())
    print(x.bit_count())
    print(1 << 5)
    return 1 << (x.bit_count()-1) == x


v = 3
print(is_pow(v))
v = 2
print(is_pow(v))
v = 32
print(is_pow(v))
v = 31
print(is_pow(v))
v = 33
print(is_pow(v))

n, q = [int(x) for x in sys.stdin.readline().split()]
A = [int(x) for x in sys.stdin.readline().split()]

juegos = []
for _ in range(q):
    inp = sys.stdin.readline().split()
    juegos.append((int(inp[0]), int(inp[1])))


def jugar(juego):
    a = 0
    b = 0
    u = 0
    p = 0
    i = 0
    for v in juego:
        if v == 1:
            u += 1
        if v % 2 == 1:
            i += 1
        if v > 1 and v >> (v.bit_count()-1) == 1:
            p += 1
            a += 1
            b += 1
