class Cerco():
    def __init__(self, c0=(0, 0), c1=(0, 0)):
        self.esperanzaMatematica_CrucesInternos = 0.0
        self.esperanzaMatematica_DeCrucesParaSalir = 0.0
        self.numeroDePuntosDeSueltos = 0
        self.hijos = []
        self.cordenada0 = c0  # (x, y)
        self.cordenada1 = c1  # (x, y)


# Pre: Los cercos ya estan resueltos
def fusionarCercos(h0: Cerco, h1: Cerco) -> Cerco:
    M = h0.numeroDePuntosDeSueltos + h1.numeroDePuntosDeSueltos
    P0 = h0.numeroDePuntosDeSueltos / M
    P1 = h1.numeroDePuntosDeSueltos / M
    P00 = P0*P0
    P01 = P0*P1
    P11 = P1*P1
    A = h0.esperanzaMatematica_DeCrucesParaSalir * \
        P01 + h0.numeroDePuntosDeSueltos * P1
    E = h0.esperanzaMatematica_CrucesInternos * P00 +\
        h1.esperanzaMatematica_CrucesInternos * P11 +\
        2*(h0.esperanzaMatematica_DeCrucesParaSalir +
           h1.esperanzaMatematica_DeCrucesParaSalir)*P01
    ret = Cerco()
    ret.esperanzaMatematica_CrucesInternos = E
    ret.esperanzaMatematica_DeCrucesParaSalir = A
    ret.numeroDePuntosDeSueltos = M
    return ret


def mergeFus(hijos: list[Cerco], L: int, R: int) -> Cerco:
    if (L == R):
        return hijos[L]
    mid = (R-L)//2
    return fusionarCercos(mergeFus(hijos, L, mid), mergeFus(hijos, mid+1, R))


def resolver(c: Cerco):
    for h in c.hijos:
        h.resolver()
    hijo = mergeFus(c.hijos, 0, len(c.hijos)-1)
    M = hijo.numeroDePuntosDeSueltos + c.numeroDePuntosDeSueltos
    Ph = hijo.numeroDePuntosDeSueltos / M
    Pp = c.numeroDePuntosDeSueltos / M
    Phh = Ph*Ph
    Php = Ph*Pp
    A = hijo.esperanzaMatematica_DeCrucesParaSalir * Ph + \
        c.esperanzaMatematica_DeCrucesParaSalir*Pp + 1
    E = hijo.esperanzaMatematica_CrucesInternos * Phh + \
        2*hijo.esperanzaMatematica_DeCrucesParaSalir*Php
    c.esperanzaMatematica_CrucesInternos = E
    c.esperanzaMatematica_DeCrucesParaSalir = A
    c.numeroDePuntosDeSueltos = M


arbol_de_cercos = Cerco()

print(resolver(arbol_de_cercos).esperanzaMatematica_CrucesInternos)
