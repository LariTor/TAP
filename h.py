from math import inf
from bisect import bisect_left, bisect_right


class Punto:
    def __init__(self, cor):
        self.cor = cor

    def __eq__(self, o):
        return self.cor[0] == o.cor[0] and self.cor[1] == o.cor[1]

    def esta_dentro(self, cerco) -> bool:
        x, y = self.cor
        x1, y1 = cerco.cor
        x2, y2 = cerco.cor2
        return x > x1 and x < x2 and y > y1 and y < y2


class Cerco(Punto):
    def __init__(self, m,  cor1=(0, 0), cor2=(0, 0)):
        Punto.__init__(self, cor1)
        self.E = 0.0
        self.A = 0.0
        self.M = m
        self.hijos = []
        self.cor2 = cor2

    def insertar_cerco(self, cerco):
        limite_derecho = bisect_right(
            self.hijos, cerco.cor[0], key=lambda c: c.cor[0])
        for i in range(limite_derecho-1, -1, -1):
            hijo = self.hijos[i]

            if hijo.esta_dentro(cerco):
                cerco.insertar_cerco(hijo)
                self.hijos[i] = cerco
                return
            elif cerco.esta_dentro(hijo):
                hijo.insertar_cerco(cerco)
                return

        # Insertar ordenado de izquierda a derecha en x
        self.hijos.insert(bisect_left(
            self.hijos, cerco.cor[0], key=lambda c: c.cor[0]), cerco)

    def insertar_punto(self, punto: Punto):
        limite_derecho = bisect_right(
            self.hijos, punto.cor[0], key=lambda c: c.cor[0])
        for i in range(limite_derecho-1, -1, -1):
            hijo = self.hijos[i]

            if punto.esta_dentro(hijo):
                hijo.insertar_punto(punto)
                return

        self.M += 1

    def __repr__(self):
        return f"<{self.M} {str(self.hijos)}>"


# Pre: Los cercos ya estan resueltos
def fusionarCercos(h0: Cerco, h1: Cerco) -> Cerco:
    M = h0.M + h1.M
    if M == 0:
        A = 0.0
        E = 0.0
    else:
        P0 = h0.M / M
        P1 = h1.M / M
        P00 = P0*P0
        P01 = P0*P1
        P11 = P1*P1
        A = h0.A * P01 + h0.M * P1
        E = h0.E * P00 + h1.E * P11 + 2*(h0.A + h1.A)*P01
    ret = Cerco(M)
    ret.E = E
    ret.A = A
    return ret


def mergeFus(hijos: list[Cerco], L: int, R: int) -> Cerco:
    if (L == R):
        return hijos[L]
    mid = (R-L)//2
    return fusionarCercos(mergeFus(hijos, L, mid), mergeFus(hijos, mid+1, R))


def resolver(c: Cerco):
    if len(c.hijos) == 0:
        c.A += 1
        return

    for h in c.hijos:
        resolver(h)
    hijo = mergeFus(c.hijos, 0, len(c.hijos)-1)
    c.M -= hijo.M
    M = hijo.M + c.M

    if M == 0:
        A = 0.0
        E = 0.0
    else:
        Ph = hijo.M / M
        Pp = c.M / M
        Phh = Ph*Ph
        Php = Ph*Pp
        A = hijo.A * Ph + \
            c.A*Pp + 1
        E = hijo.E * Phh + \
            2*hijo.A*Php

    c.E = E
    c.A = A
    c.M = M


N, M = map(int, input().split())

input_cercos = [list(map(int, input().split())) for i in range(N)]
input_puntos = [tuple(map(int, input().split())) for i in range(M)]


input_puntos.sort(key=lambda p: p[0])

base = 2**(M-1).bit_length()

range_tree = [0] * (base-1) + input_puntos + [(inf, inf)] * (base - M)


def build_up(i: int) -> list[int, int, int, list[list[int, int, int]]]:
    if i >= base-1:
        cor = range_tree[i]
        meta = [[cor[1], None, None]]
        range_tree[i] = [cor[0], (cor[0], cor[0]), meta]
        return [cor[0], cor[0], cor[0], meta]
    L = build_up(2*i+1)
    R = build_up(2*i+2)
    minL = min(L[0], L[1])
    minR = min(R[0], R[1])
    maxR = R[2]
    metaL = L[3]
    metaR = R[3]
    j = 0
    k = 0
    meta = []
    while j < len(metaL) and k < len(metaR):
        if metaL[j][0] < metaR[k][0]:
            meta.append([metaL[j][0], j, k])
            j += 1
        else:
            meta.append([metaR[k][0], j, k])
            k += 1
    while j < len(metaL):
        meta.append([metaL[j][0], j, inf])
        j += 1
    while k < len(metaR):
        meta.append([metaR[k][0], inf, k])
        k += 1
    range_tree[i] = [R[0], (minL, maxR), meta]
    return [minL, minR, maxR, meta]


def querry(cerco: list[int, int, int, int], i: int, y: int) -> int:
    curr = range_tree[i]
    # Es una hoja
    if i >= base-1:
        # print('curr', curr, 'x', curr[0], 'y', curr[2][0][0])
        return int(Punto((curr[0], curr[2][0][0])).esta_dentro(
            Cerco(0, (cerco[:2]), (cerco[2:]))))
    xl = cerco[0]
    xr = cerco[2]
    # Contiene el rango
    if xl <= curr[1][0] and curr[1][1] <= xr:
        # print('Contiene', curr, 'rl', curr[1][0], 'rr', curr[1][1])
        j = y
        while j < len(curr[2]) and curr[2][j][0] <= xr:
            # print('y', curr[2][0][j])
            j += 1
        return j - y
    # Completamente disjunto
    if xr < curr[1][0] or curr[1][1] < xl:
        # print('Disjunto', curr, 'rl', curr[1][0], 'rr', curr[1][1])
        return 0
    # Contiene el rango parcialmente
    # print('Else', curr, 'rl', curr[1][0], 'rr', curr[1][1], 'xl', xl, 'xr', xr)
    # print('L', range_tree[2*i+1][0])
    L = querry(cerco, 2*i+1, curr[2][y][1])
    # print('R', range_tree[2*i+2][0])
    R = querry(cerco, 2*i+2, curr[2][y][2])
    return L + R


build_up(0)


raiz = Cerco(M, (-inf, -inf), (inf, inf))


cercos = []


for input_cerco in input_cercos:
    y = bisect_left(range_tree[0][2], input_cerco[1], key=lambda m: m[0])
    m = querry(input_cerco, 0, y)
    cerco = Cerco(m, (input_cerco[:2]), (input_cerco[2:]))
    cercos.append(cerco)


for cerco in cercos:
    raiz.insertar_cerco(cerco)

resolver(raiz)
print(raiz.E)

'''
cerco = [20, 20, 60, 80]
print("TEST", cerco)
y = bisect_left(range_tree[0][2], cerco[1], key=lambda m: m[0])
print("range_tree", range_tree)
print(querry(cerco, 0, y))
'''
