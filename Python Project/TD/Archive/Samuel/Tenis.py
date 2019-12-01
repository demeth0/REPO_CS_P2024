# -*- coding: utf-8 -*-
"""
Created on Fri Nov 22 09:55:49 2019

@author: samde
"""

"""
quand un des deux joueur a 2 points de différence avec l'autre il gagne le jeu

pour gagner un set il faut 2 jeu d'avance

6 jeu = 1 set

pour gagner il faut 2 jeu d'avance sur l'autre

6 jeu max par joueurs

pour gagner la partie il faut 2 set d'avance

/!\ : si le joueur arrive a 6 jeu et qui y a pas 2 jeu de diff : JEU DECISIF
-> on compte les points de 1 a 7, il faut deux points de diff pour gagner un set

Brouillon :
    
def jeu_v1():
    point_j1 = 0
    point_j2 = 0
    
    joueur_1_gagnant = None
    jeu_finis = False
    while jeu_finis != True :
        gagnant = int (input("quel joueur a gagner le point ? 1 ou 2\n"))
        if gagnant == 1 :
            point_j1 += 1 
        elif gagnant == 2:
            point_j2 += 1
        
        jeu_finis, joueur_1_gagnant = j1_as_win_jeu(point_j1,point_j2)
    if joueur_1_gagnant == True :
        print("joueur 1 a gagner")
    else:
        print("joueur 2 a gagner")

#"""

def j1_as_win_jeu(score_j1,score_j2):
    diff_score = score_j1-score_j2
    j_as_win = False
    j1_win = None

    if diff_score >=2 :
        j1_win = True
        j_as_win = True
    elif diff_score <= -2:
        j1_win = False
        j_as_win = True
    return j_as_win,j1_win

def jeu_v2(liste_de_point):
    point_j1 = 0
    point_j2 = 0
    
    joueur_1_gagnant = None
    jeu_finis = False
    for g in list(liste_de_point):
        gagnant = int(g)
        if gagnant == 1 :
            point_j1 += 1 
        elif gagnant == 2:
            point_j2 += 1
        
        jeu_finis, joueur_1_gagnant = j1_as_win_jeu(point_j1,point_j2)
        
    if jeu_finis == True:
        if joueur_1_gagnant == True :
            print("joueur 1 a gagner le jeu")
        else:
            print("joueur 2 a gagner le jeu")
        return joueur_1_gagnant

def set_tennis():
    set_gagnant_j1 = 0
    set_gagnant_j2 = 0
    partie_finie = False
    set_decisif = False
    #tant que le score des deux joueurs est différent et strictement plus petit que 6 ou le score des deux joueurs est 6 et egal (set decisif)
    while partie_finie == False:
        jeu = input("entrez le score:\n")
        j1_win = jeu_v2(jeu)
        if j1_win == True :
            set_gagnant_j1 += 1
        else :
            set_gagnant_j2 += 1
            
        if abs(set_gagnant_j1-set_gagnant_j2)>=2:
            partie_finie = True
        elif set_gagnant_j1==6 and set_gagnant_j2==6 :
            partie_finie = True
            set_decisif = True
    
    j1_win = None
    if partie_finie == True and set_decisif == False :
        if set_gagnant_j1-set_gagnant_j2>0:
            print("joueur 1 a gagner le set")
            j1_win = True
        else:
            print("joueur 2 a gagner le set")
            j1_win = False
    else:
        j1_win = jeu_decisif()
    return j1_win

def jeu_decisif():
    j1_win = jeu_v2(input("ecrir les score du j1 et j2 : ex 1122212121211\n")) 
    if j1_win == True :
        print("joueur 1 a gagner")
    else:
        print("joueur 2 a gagner")
    return j1_win

def match(nb_set_gagnant):
    set_j1 = 0
    set_j2 = 0
    while set_j1 < nb_set_gagnant and set_j2 < nb_set_gagnant :
        j1_win = set_tennis()
        if j1_win == True :
            set_j1 += 1
        else:
            set_j2 += 1
    if set_j1 == nb_set_gagnant :
        print("joueur 1 remporte le match")
    else:
        print("joueur 2 remporte le match")