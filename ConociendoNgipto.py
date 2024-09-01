import sys 

n = int(sys.stdin.readline())
c = [int(x) for x in sys.stdin.readline().split()]
s = [int(x) for x in sys.stdin.readline().split()]

base = []

for _ in range(n):
    b = [int(x) for x in sys.stdin.readline().split()]
    base.append(b)

def sombra(C, S):
    v = C[2] / (C[2]-S[2])
    x = C[0] + (C[0]-S[0]) * v
    y = C[1] + (C[1]-S[1]) * v
    return [x, y]

def centro(B):
    x = 0
    y = 0
    for b in B:
        x += b[0]
        y += b[1]
    x /= len(B)
    y /= len(B)
    return [x, y]

def cruce(A, B, C, D):
    div0 = C[0]-D[0]
    if div0 == 0:
        div0 = 1
    div1 = C[1]-D[1]
    if div1 == 0:
        div1 = 1
    alf0 = (A[0]-C[0])/(div0)
    alf1 = (A[1]-C[1])/(div1)
    alf2 = (A[1]-D[1])/(div1)
    alf3 = (A[0]-D[0])/(div0)
    divalf = alf2-alf3
    if divalf == 0:
        return True
    alf = (alf0-alf1)/(divalf)
    bet = (A[0]-C[0]+(A[0]-B[0])*alf)/(div0)
    return -1 < bet and bet <= 0 and -1 < alf 

def cruza(p, c, B):
    cruzes = 0
    for i in range(len(B)):
        i_n = (i+1)%len(B)
        if cruce(p, c, B[i], B[i_n]):
            cruzes += 1
    return cruzes


def adentro(p, B):
    c = p
    c[0] += 1
    c[1] += 1
    cruces = 0
    for i in range(len(B)):
        i_n = (i+1)%len(B)
        if cruce(p, c, B[i], B[i_n]):
            cruces += 1
    return cruces % 2 == 1

som = sombra(c, s)
if not adentro(som, base):
    print("S")
elif adentro(c[:2], base):
    print("S" if cruza(som, c[:2], base) > 0 else "N")
else:
    print("S" if cruza(som, c[:2], base) != 1 else "N")

