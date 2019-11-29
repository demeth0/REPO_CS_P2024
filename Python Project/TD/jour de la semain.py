# -*- coding: utf-8 -*-
"""
Éditeur de Spyder

Ceci est un script temporaire.
"""
"""
Jour de la semaine

affiche le jours de la semaine correspondant a la date choisit par rapport a la date du 1er janvier 1973 supposer un lundi

"""

#question 1
#retourne vrai si la date est bissextile
def watch_if_bissextile (annee) : 
    bissextilité1 = annee % 4
    
    annee_bisextile=False
    if (bissextilité1 == 0)   :
        annee_bisextile=True
        
    return annee_bisextile



#question 2 3 4 

#saisir la date a déterminer
annee = int (input ("veuillez entrer l'année\n"))
mois = int (input ("veuillez entrer le mois\n"))
jour = int (input ("veuillez entrer le jour\n"))

#liste des nombre de jours par mois 
liste_nb_jour_mois = [31,0,31,30,31,30, 31,31,30,31,30,31]
if watch_if_bissextile(annee) == False :
    liste_nb_jour_mois [1] = 28
else :
    liste_nb_jour_mois [1] = 29


#calcule le nombre de jours du début de l'annee jusqu'au mois et jour préciser
def mois_jours_to_jours(_jours,_mois):
    nb_jour_mois = 0    
    for numero_mois in range (0,_mois-1) :
        nb_jour_mois = liste_nb_jour_mois [numero_mois] + nb_jour_mois
    
    nb_jours_total = _jours+nb_jour_mois
    return nb_jours_total
"""
retourne le nombre de jours entre deux années du début de la premiere jusqu'au premier janvier de la derniere date exclus
"""
def nb_jours_btw_2a(_annee1, _annee2):
    nb_jours_total = 0
    nb_jours_annee_bissextile = 366
    nb_jours_annee_non_bissextile = 365
    for year in range(_annee2, _annee1-1):
        if watch_if_bissextile(year) ==True :
            nb_jours_total = nb_jours_total + nb_jours_annee_bissextile
        else:
            nb_jours_total = nb_jours_total + nb_jours_annee_non_bissextile
    return nb_jours_total
    
#constante date de référence
annee2 = 1973

"""
nb_jours_entre_deux_jours = 
    nb_jours_btw_2a(annee, annee2)         calcul le nimbre de jours du 1er janvier 1973 jusqu'a l'annee indiquer
                +
    mois_jours_to_jours(jour, mois)        calcul le nimbre de jours apres la derniere annee

"""
nb_jours_entre_deux_jours = nb_jours_btw_2a(annee, annee2)+mois_jours_to_jours(jour, mois)

liste_jour = ["lundi","mardi","mercredi","jeudi","vendredi","samedi","dimanche"]
print(liste_jour[nb_jours_entre_deux_jours % 7])