
import random

def modpow(a, b, p):
    if b == 0: return 1
    else:
        mm = modpow(a, b / 2, p)
        res = (mm * mm) % p
        if b % 2 == 1: res = (res * a) % p
        return res

def MRTest1(a, p):
    d = p - 1
    s = 0
    while d % 2 == 0:
        s += 1
        d /= 2
    k = modpow(a, d, p)
    if k == 1: return True
    ss = 0
    while ss <= s:
        if (k + 1) % p == 0: return True
        k = (k * k) % p
        ss += 1
    return False
def MRTest(p):
    r = random.Random()
    for i in range(20):
        a = r.randint(2, p - 1)
        if not MRTest1(a, p): return False
    return True

def find_prime(pp):
    while not MRTest(pp):
        pp += 2
    return pp

a = find_prime(9242984980983797311)
b = find_prime(9894375252459370111)
p = a * b
print a, b, p
print MRTest(p)
print modpow(3, p - 1, p)

