n = 9145356185469980673640298696124239
# n = 91453561854699727196729211565114858349

def gcd(x, y):
    while True:
        if x == 0:
            return y
        elif y == 0:
            return x
        x, y = y, x % y

def g(x):
    return (x * x + 1) % n

def gg(x):
    return g(g(x))

def work():
    x = 1
    y = 1
    pp = 1
    count = 0
    while True:
        x = g(x)
        y = gg(y)
        pp = (abs(x - y) * pp) % n
        count += 1
        if count % 100 == 0:
            if gcd(pp, n) != 1: break
        if count % 100000 == 0:
            print count
    print "ans = ", pp


# print gcd(71783705101351325303687721409436432804, \
#           91453561854699727196729211565114858349)
# work()

print gcd(n, 4793331577026082304589875637532023)

