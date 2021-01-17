# -*- coding: utf-8 -*-
"""
Created on Sun Dec  8 19:47:27 2019

librairie pour les opérations de base sur les matrices

@author: Samuel Dechambre
"""

# =============================================================================
# creation de matrices / copie
# =============================================================================

"""
en compréhension
def create_matrice(row,column,value):
    matrice=[None]*row
    for i in range(row):
        matrice[i]=[value]*column
    return matrice
"""
#optimiser
def create(row,column,v):
    return [[v]*column for i in range(row)]

"""
en compréhenson

def copie_matrice(matrice):
    row = len(matrice)
    matrice_copy = [None]*row
    for i in range(row):
        matrice_copy[i]=matrice[i][:]    #r[i] = m[i] alors ce n'est pas une copie (pointeur)
    return matrice_copy
#"""
def copy(matrice):
    return [matrice[i][:] for i in range(len(matrice))]

# =============================================================================
# opération sur les matrices
# =============================================================================
    
#retourne les dimensions de la matrice si la matrice est valide
def getDimention(m):
    row = len(m)
    assert row>0 #verifie si la condition est juste sinon arrete le programe
    column=len(m[0])
    for col in m:
        assert len(col)==column
    return (row,column)
"""
en compréhension
#symétrie de la matrice par rapport a la diagonale
def transposition_de_matrice(m):
    row,column = getDimention(m)
    t = create(column,row,None)
    for j in range(column):
        for i in range(row):
            t[j][i]=m[i][j]
    return t
"""
def transpose(m):
    row,column = getDimention(m)
    return [[m[i][j] for i in range(row)] for j in range(column)]
        
def times(a,b):
    n,p = getDimention(a)
    q,r = getDimention(b)
    assert q==p
    c = create(n,r,0)
    for i in range(n):
        for j in range(r):
            for k in range(p):
                c[i][j] += a[i][k]*b[k][j]
    return c