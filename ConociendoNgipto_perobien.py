import sys

n = int(sys.stdin.readline())
c = [int(x) for x in sys.stdin.readline().split()]
s = [int(x) for x in sys.stdin.readline().split()]

base = []

for _ in range(n):
    b = [int(x) for x in sys.stdin.readline().split()]
    base.append(b)


def diff(a, b):
    za = 0 if len(a) < 3 else a[2]
    zb = 0 if len(b) < 3 else a[2]
    return [a[0] - b[0], a[1]-b[1], za - zb]


def cross(v1, v2):
    x = v1[1] * v2[2] - v1[2] * v2[1]
    y = v1[2] * v2[0] - v1[0] * v2[2]
    z = v1[0] * v2[1] - v1[1] * v2[0]
    return [x, y, z]


def dot(v1, v2):
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]


def solucion():
    for i in range(n):
        nor = cross(diff(base[i], base[(i+1) % n]), diff(c, base[i]))
        c_c = dot(c, nor)
        c_s = dot(s, nor)
        if c_s < c_c:
            return True
    return False


print("S" if solucion() else "N")
