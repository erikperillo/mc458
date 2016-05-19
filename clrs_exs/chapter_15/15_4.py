#!/usr/bin/env python2.7

import numpy as np

#exercise 15.4.1
def lcs(x, y):
    m = len(x)
    n = len(y)
    c = np.zeros(shape=(m+1, n+1), dtype=int)    
    s = np.zeros(shape=(m+1, n+1), dtype=str)    

    for i in range(m):
        for j in range(n):
            if x[i] == y[j]:
                c[i+1, j+1] = 1 + c[i, j]
                s[i+1, j+1] = "d"
            else:
                c[i+1, j+1] = max(c[i+1, j], c[i, j+1])
                s[i+1, j+1] = "u" if c[i+1, j+1] == c[i, j+1] else "l"

    return c, s

def l(n):
    return n - 1

def lcs_efficient(x, y):
    m = len(x)
    n = len(y)

    if m > n:
        x, y = y, x
        m, n = n, m

    c = (m+1)*[0]

    for i in range(n):
        diag = 0
        for j in range(1, m+1):
            if x[j-1] == y[i]:
                aux = 1 + diag
            elif c[j] >= c[j-1]:
                aux = c[j]
            else:
                aux = c[j-1]
            diag = c[j]
            c[j] = aux

    return c[m] 

#15.4.5
def seq_num(seq):
    return lcs(seq, sorted(seq))

#exercise 15.4.3
def _lcs_memo(x, y, c, m, n):
    if c[m, n] >= 0:
        return c[m, n]

    if m == 0 or n == 0:
        c[m, n] = 0
    elif x[m-1] == y[n-1]:
        c[m, n] = 1 + _lcs_memo(x, y, c, m-1, n-1)
    else:
        c[m, n] = max(_lcs_memo(x, y, c, m, n-1), _lcs_memo(x, y, c, m-1, n))

    return c[m, n]

def lcs_memo(x, y):
    m = len(x)
    n = len(y)
    c = -1*np.ones(shape=(m+1, n+1), dtype=int)    

    _lcs_memo(x, y, c, m, n)

    return c[m, n]

def build_lcs(s, x, m, n):
    if m == 0 or n == 0:
        return ""
    elif s[m, n] == "d":
        return build_lcs(s, x, m-1, n-1) + str(x[m-1])
    elif s[m, n] == "u":
        return build_lcs(s, x, m-1, n)
    else:
        return build_lcs(s, x, m, n-1)

def build_lcs_num(s, x):
    return build_lcs(s, x, len(x), len(x))

#exercise 15.4.2
def _build_lcs(c, x, m, n):
    if m == 0 or n == 0:
        return ""
    elif c[m, n] - 1 == c[m-1, n-1]:
        return _build_lcs(c, x, m-1, n-1) + x[m-1]
    elif c[m-1, n] >= c[m, n-1]:
        return _build_lcs(c, x, m-1, n)
    else:
        return _build_lcs(c, x, m, n-1)

def main():
    x = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA"
    y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA"
    #input for exercise 15.4.1
    #x = "10010101"
    #y = "010110110"
    nx = [2,3,2,1,5,3,2,5]

    c, s = lcs(x, y)
    #lcs_xy = build_lcs(s, x, len(x), len(y))
    lcs_xy = _build_lcs(c, x, len(x), len(y))

    print "lcs(%s, %s):\n\t%s" % (x, y, lcs_xy)
    print "lcs = %d" % c[len(x), len(y)]
    print "lcs_mem = %d" % lcs_memo(x, y)
    print "lcs_efficient = %d" % lcs_efficient(x, y)
    
    c, s = seq_num(nx)
    print "seq_num(", nx, ") =", c[len(nx)]
    print build_lcs_num(s, nx)

if __name__ == "__main__":
    main()
