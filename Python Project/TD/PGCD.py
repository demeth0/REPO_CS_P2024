# -*- coding: utf-8 -*-
"""
Spyder Editor

"""

def PGCD(_a, _b):
    reste = 0
    a = _a
    b = _b
    while(b != 0):	#PGCD(a,b) == PGCD(b,a-b) == ... == PGCD(pgcd, 0)
        reste = a%b
        a = b
        b = reste
    print(a)