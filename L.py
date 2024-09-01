import sys


n, q = [int(x) for x in sys.stdin.readline().split()]
A = [int(x) for x in sys.stdin.readline().split()]

juegos = []
for _ in range(q):
    inp = sys.stdin.readline().split()
    juegos.append((int(inp[0]), int(inp[1])))


def is_pow(x):
    return x.bit_count() == 1


unos = [0]
potencias = [0]
impares = [0]


def prep():
    u = 0
    p = 0
    i = 0
    for v in A:
        if v == 1:
            u += v
        elif (v % 2) == 1:
            i += v
        elif is_pow(v):
            p += v
        unos.append(u)
        impares.append(i)
        potencias.append(p)


def jugar(L, R):
    u = unos[R] - unos[L]
    p = potencias[R] - potencias[L]
    i = impares[R] - impares[L]
    a = ((u//2) + (u % 2)) + p
    b = (u//2) + i
    if a > b:
        return "A"
    if a == b:
        return "E"
    if a < b:
        return "B"


prep()
for L, R in juegos:
    print(jugar(L-1, R))
