# -*- coding: utf-8 -*-
"""
Spyder Editor

"""

def Hamming(tab_a, tab_b):
    diff = 0
    for i in range(len(tab_a)):
        if(tab_a[i] != tab_b[i]):
            diff = diff+1
    return diff
    