#!/usr/bin/env python2.7

"""
exercise 15.2.1:
find optimal parenthesization for matrix chain multiplication
[5, 10, 3, 12, 5, 50, 6]
"""

import numpy as np

def get_indexes_mat(dim):
   return np.array(dim*[dim*[-1]])

#determines costs and indexes for best parenthesization
def mat_chain_order(b):
    n = len(b) - 1
    m = get_indexes_mat(n) 
    s = get_indexes_mat(n) 

    for i in range(n):
        m[i, i] = 0

    for l in range(2, n+1):
        for i in range(n - l + 1):
            j = i + l - 1
            for k in range(i, j):
                q = m[i, k] + m[k+1, j] + b[i]*b[k+1]*b[j+1]
                if m[i, j] < 0 or q < m[i, j]: 
                    m[i, j] = q
                    s[i, j] = k

    return m, s

#prints solution for best parenthesization
def get_mat_chain_order_str(s, i, j):
    if i == j:
        return "M%d" % i
    else:
        return "(" + \
            get_mat_chain_order_str(s, i, s[i][j]) + \
            "*" + \
            get_mat_chain_order_str(s, s[i][j] + 1, j) + \
            ")"

def main():
    b = [5, 10, 3, 12, 5, 50, 6]

    m, s = mat_chain_order(b)
   
    print "m =", m
    print
    print "s =", s 
    print 
    print "solution:"
    print get_mat_chain_order_str(s, 0, len(b)-2)

if __name__ == "__main__":
    main()
