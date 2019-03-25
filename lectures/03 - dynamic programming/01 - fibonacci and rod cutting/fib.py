def fib(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fib(n-1) + fib(n-2)

def fib_v2(n, mem):
    if n == 0:
        return 0
    if n == 1:
        return 1
    
    #is the recursive call necessary?
    n1 = 0
    n2 = 0
    if (n-1 in mem) == False:
        n1 = fib_v2(n - 1, mem)
    else:
        n1 = mem[n-1]
    if (n-2 in mem) == False:
        n2 = fib_v2(n - 2, mem)
    else:
        n2 = mem[n-2]

    #store in lookup table for future resue
    mem[n-1] = n1
    mem[n-2] = n2

    return n1 + n2

def bu_fib(n):
    current = 0
    prev = 1
    next = 0
    for i in range(n):
        next = current + prev
        prev = current
        current = next
    return current

for i in range(100):
    print(bu_fib(i))
