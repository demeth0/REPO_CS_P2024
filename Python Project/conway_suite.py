# -*- coding: utf-8 -*-
"""
Created on Fri Jan 10 20:59:05 2020

@author: Samuel Dechambre
"""

TERM_0 = "1"
TERM_N = 56

def generateNextTerm(lst_term):
    lst_result = []
    #pas fini de parcourir le liste
    j = 0
    while j < len(lst_term):
        consecutive_indetity = 1
        while j+1 < len(lst_term) and lst_term[j] == lst_term[j+1]:
            consecutive_indetity += 1
            j = j+1
        lst_result += [str(consecutive_indetity), str(lst_term[j])]
        j += 1
    return lst_result
            

lst_r = [TERM_0]
for i in range(1,TERM_N):
    lst_r = generateNextTerm(lst_r)
    
    
#si ca lag trop supprimer la ligne print ici et aller dans variable explorer -> str_l -> clic droit -> copier
print(len(lst_r))