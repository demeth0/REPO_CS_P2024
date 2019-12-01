# -*- coding: utf-8 -*-
"""
Created on Thu Nov 28 15:23:48 2019

@author: samde
"""
"""
-> tableau et multiplication (feuille 2)
exercice 3(CF TP)

"""

def is_symetric(matrice):
    is_symetric = len(matrice)==len(matrice[0])
    if is_symetric :
        for i in range(len(matrice)):
            for j in range(len(matrice[i])):
                if matrice[i][j] != matrice[j][i] :
                    is_symetric = False
                    break
    return is_symetric

def matrice():
    a=[[1,2],[3,4]]
    b=[[5,6],[7,8]]
    #addition de tab pas de matrices
    print((a+b))
    
def creer_matrice(ligne, colonne):
    return [[None]*ligne for i in range(colonne)]
    
def somme_matrice(m1, m2):
    assert len(m1)==len(m2) and len(m1[0])==len(m2[0])
    matrice_somme = [[None]*len(m1[0]) for i in range(len(m1))]
    for i in range(len(m1)):
        for j in range(m1[0]):
            matrice_somme[i][j] = m1[i][j] + m2[i][j]
    return matrice_somme

def prod_matrice_nombre(x,m):
    matrice_prod = 