# -*- coding: utf-8 -*-
"""
Created on Sun Nov 10 14:16:11 2019

@author: a_bro
"""
import sys
 n = int(input("veuillez entrer la taille de votre tableau: "))
    for i in range(n):
        tab_bit.append(int(input("Veuillez entrer en bit les valeurs du tableau : ")))
        print(tab_bit)
    for k in tab_bit :
        if k ==0 or k == 1 :
            print("le tableau a les bonnes valeurs")
        else :
            print("vous avez entrez de mauvaises valeurs, vous allez recommencer le programme")
            sys.exit
 
def group_null_maxi(tab_bit) :
    indice0 = 0
   
    for j in tab_bit:
        if j == 0 :
            indice0 += 1
            element_nul = indice0
        elif j == 1 :
            indice0 = 0
            
    print("le groupe nulle le plus grand est de", element_nul)
group_null_maxi(tab_bit)
        
