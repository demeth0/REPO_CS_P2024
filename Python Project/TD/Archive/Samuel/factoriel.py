# -*- coding: utf-8 -*-
"""
Spyder Editor

"""
    
def factoriel(n):
    n_total = 1
    for i in range(1, n+1):
        n_total = n_total * i
        
    print(n_total)