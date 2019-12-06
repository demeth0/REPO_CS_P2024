# -*- coding: utf-8 -*-
"""
Created on Fri Nov 22 09:55:49 2019

@author: Samuel Dechambre
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

JOUEUR_1 = 1
JOUEUR_2 = 2
PAS_DE_VAINQUEUR = -1

#si il n'y a pas de vainqueur alors retourne -1
def jeu(score_j1,score_j2):
    diff_score = score_j1-score_j2

    winner = PAS_DE_VAINQUEUR
    #score_j1 >=2+score_j2
    if diff_score >=2 :
        winner = JOUEUR_1
    #score_j1 <=2+score_j2
    elif diff_score <= -2:
        winner = JOUEUR_2
    return winner

def jeu_v2(liste_de_point):
    point_j1 = 0
    point_j2 = 0
    winner = None
    for str_point in list(liste_de_point):
        int_point = int(str_point)
        if int_point == 1 :
            point_j1 += 1 
        elif int_point == 2:
            point_j2 += 1
        
        winner = jeu(point_j1,point_j2)
        
    if winner != PAS_DE_VAINQUEUR:
        if winner == JOUEUR_1:
            print("joueur 1 a gagner le jeu")
        elif winner == JOUEUR_2:
            print("joueur 2 a gagner le jeu")
    return winner

def set_tennis():
    set_gagnant_j1 = 0
    set_gagnant_j2 = 0
    partie_finie = False
    set_decisif = False
    #tant que le score des deux joueurs est différent et strictement plus petit que 6 ou le score des deux joueurs est 6 et egal (set decisif)
    while partie_finie == False:
        #on suppose que le score permet de déterminer un vainqueur du jeu
        winner = PAS_DE_VAINQUEUR
        while(winner == PAS_DE_VAINQUEUR):
            scores = input("entrez le score:\n")
            winner = jeu_v2(scores)
            
        if winner == JOUEUR_1 :
            set_gagnant_j1 += 1
        elif winner == JOUEUR_2 :
            set_gagnant_j2 += 1
            
        if abs(set_gagnant_j1-set_gagnant_j2)>=2:
            partie_finie = True
        elif set_gagnant_j1==6 and set_gagnant_j2==6 :
            partie_finie = True
            set_decisif = True
    
    winner = PAS_DE_VAINQUEUR
    if partie_finie == True and set_decisif == False :
        if set_gagnant_j1-set_gagnant_j2>0:
            print("joueur 1 a gagner le set")
            winner = JOUEUR_1
        else:
            print("joueur 2 a gagner le set")
            winner = JOUEUR_2
    else:
        winner = jeu_decisif()
    return winner

def jeu_decisif():
    print("jeu décisif !")
    winner = PAS_DE_VAINQUEUR
    while(winner == PAS_DE_VAINQUEUR):
        scores = input("entrez le score:\n")
        winner = jeu_v2(scores)
    
    if winner == JOUEUR_1:
        print("joueur 1 a gagner le jeu décisif")
    elif winner == JOUEUR_2:
        print("joueur 2 a gagner le jeu décisif")
    return winner

def match(nb_set_gagnant):
    set_j1 = 0
    set_j2 = 0
    while set_j1 < nb_set_gagnant and set_j2 < nb_set_gagnant :
        winner = set_tennis()
        if winner == JOUEUR_1 :
            set_j1 += 1
        elif winner == JOUEUR_2:
            set_j2 += 1
    if set_j1 == nb_set_gagnant :
        print("joueur 1 remporte le match")
    else:
        print("joueur 2 remporte le match")