import sys 

n,x = [int(x) for x in sys.stdin.readline().split()]
b = [int(x) for x in sys.stdin.readline().split()]

b.sort()

def swap(x1,x2):
    aux = b.pop(x2)
    b.insert(x1, aux)   

fail = False

for i in range(n-1):
    if b[i] + b[i+1] == x:  
        if b[i+1] != b[-1]:
            swap(i+1, -1)
        elif b[i] != b[0]:
            swap(i,0)
        else: 
            sys.stdout.write("*\n")
            fail = True
            break

if not fail:    
    for c in range(len(b)-1):
        sys.stdout.write(str(b[c])+' ')
    sys.stdout.write(str(b[-1])+'\n')
