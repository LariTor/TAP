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

    def __repr__(self):
        return f"<{self.cor}>"


class Cerco(Punto):
    def __init__(self, cor1=(0, 0), cor2=(0, 0)):
        Punto.__init__(self, cor1)
        self.E = 0.0
        self.A = 0.0
        self.M = 0
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
        return f"<{self.cor} {self.cor2} {self.M} {str(self.hijos)}>"


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


def ltt(ls: list) -> list[tuple]:
    return [tuple(ls[:2]), tuple(ls[2:])]


class Cierre(Punto):

    def __init__(self, c: Cerco):
        Punto.__init__(self, c.cor2)
        self.cer = c


def cierre(c: Cerco) -> [Cerco, Cierre]:
    return [c, Cierre(c)]


def flatten(xss):
    return [x for xs in xss for x in xs]

# ---------------------------------------------------------------------------------


N, M = map(int, input().split())

input_cercos = [Cerco(*ltt(list(map(int, input().split())))) for i in range(N)]
input_puntos = [Punto(tuple(map(int, input().split()))) for i in range(M)]

raiz = Cerco((-inf, -inf), (inf, inf))
input_cercos.append(raiz)

todos = flatten(list(map(cierre, input_cercos))) + input_puntos
todos.sort(key=lambda p: p.cor[0])

print("-----------")
print(todos)
print("-----------")


resolver(raiz)
print(raiz.E)
