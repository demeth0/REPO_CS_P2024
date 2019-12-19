#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@author: celian
"""


def init_fusion(liste):
    milieu = len(liste)//2
    tri_fusion(liste, 0, milieu, len(liste))
    return liste

def tri_fusion(tmp, gauche, milieu, droite):
    
    
    
    if not gauche == milieu:
            milieu1 = (gauche + milieu) // 2
            tri_fusion(tmp, gauche, milieu1, milieu)
        
    if not milieu == droite-1:
            milieu2 = (milieu + droite) // 2
            tri_fusion(tmp, milieu, milieu2, droite)
        
        
    fusion(tmp, gauche, milieu, droite-1)
    
    
    
    

    
def fusion(liste, gauche, milieu, droite):
    
    nb_elems = droite - gauche + 1
    tmp = []
    
    gauche_init = gauche
    milieu_init = milieu
    
    i = 0
    while i < nb_elems:
        
        if liste[gauche] >= liste[milieu] :
            
            tmp.append(liste[milieu])
            milieu += 1
            
        else :
            
            tmp.append(liste[gauche])
            gauche += 1
            
        i += 1
        
        #petite optimisation
        if gauche == milieu_init:
            tmp += liste[milieu:droite+1]
            i = nb_elems
            
        elif milieu == droite + 1:
            tmp += liste[gauche:milieu_init]
            i = nb_elems
        
        
    liste[gauche_init:droite+1] = tmp
    return liste
#test
#print(init_fusion([20,19,18,17,16,15,14,13,12,11,10,9,8,7,4,5,6,3,2,1,0]))
