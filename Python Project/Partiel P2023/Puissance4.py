# -*- coding: utf-8 -*-
"""
Created on Fri Oct 18 10:12:35 2019

@author: abant
"""
# Programme du jeu Puissance4, inspiré du partiel de CS111 de 2018/2019.
#
# Certaines fonctions ont été modifiées dans leur comportement par rapport 
# aux consignes données.
#
# Les modifications sont répertoriées dans la description.
#
# Les fonctions de vérifications des 4 pions alignées n'étaient pas demandé
# et ont été créée de zéro.
#
# Elles seront expliquées du mieux possible.
#
# Notations fonctions: (Le numéro de l'exercice suit les fonctions)
#
#     PARTIEL : Suit exactement la consigne de l'exercice.
#
#     MODIF : Suit partiellement la consigne de l'exercice,
#     mais diverge du fonctionnement exact demandé.
#
#     ORIGINAL : Non demandée, ont été créée spécialement pour faire
#     marcher le jeu.
#
# Les noms des fonctions ont été traduite en Rançais,
# pour une meilleure compréhension.
#
# V1.01


def creer_matrice(Colonne,Ligne,Initialisation): #PARTIEL : Exercice 1.1
    return[[Initialisation]*Colonne for indice in range(Ligne)]
#    Créer et initialise une matrice de Colonne * Ligne avec
#    Initialisation la valeur d'Initialisation


def recracher_matrice(Matrice): #PARTIEL : Exercice 1.2
    for indice in range(len(Matrice)):
        print(Matrice[indice])
#    Affiche une matrice Matrice données en paramètre lignes par lignes
    
    
def dedans_matrice(Colonne,Ligne,Matrice):  #PARTIEL : Exercice 1.3
    Resultat = True
    if not(Colonne >= 1 and Colonne <= len(Matrice[0])+1):
        Resultat = False
    elif not(Ligne >= 1 and Ligne <= len(Matrice)+1):
        Resultat = False
    return Resultat
#    Vérifie si des coordonnées Colonne et Ligne sont comprises
#    dans une Matrice tous donnés en paramètre
    

def creer_plateau_jeu():  #PARTIEL : Exercice 2.1
    return creer_matrice(7,6,' ')
#    Initialise un tableau de jeu


def recracher_plateau_jeu(Plateau_de_jeu): #PARTIEL : Exercice 3.1
    recracher_matrice(Plateau_de_jeu)
#    Affiche un plateau de jeu
    
    
def insertion_colonne_possible(Colonne,Plateau_de_jeu): #PARTIEL : Exercice 4.1
    return (Plateau_de_jeu[0][Colonne] == ' ')
#    Retourne s'il est possible d'insérer un pion dans une Colonne
#    dans un Plateau_de_jeu tous deux donnés en paramètre


def jeu_plein(Plateau_de_jeu): #PARTIEL : Exercice 4.2
    Resultat = False
    Recurrence = 0
    for indice in range(0,7):
        if (Plateau_de_jeu[0][indice] != ' '):
            Recurrence += 1
            if Recurrence == 7:
                Resultat = True
    return Resultat
#    Retourne si le plateau de jeu donné en paramètre est plein
    

def determiner_ligne_insertion(Colonne,Plateau_de_jeu): #PARTIEL : Exercice 4.3
    curseur = 5
    while (Plateau_de_jeu[curseur][Colonne] != ' '):
        curseur -= 1
    return curseur
#    Donne la ligne d'insertion possible dans une Colonne 
#    dans un Plateau de jeu tous deux donnés en paramètre

def inserer_piece(Colonne,Symbole,Plateau_de_jeu): #MODIF : Exercice 4.4
    Ligne = determiner_ligne_insertion(Colonne,Plateau_de_jeu)
    Plateau_de_jeu[Ligne][Colonne] = Symbole
    return Ligne
#    Insère la pièce de couleur Symbole dans la colonne du plateau de jeu
#    Modif : retourne la ligne dont laquelle la pièce est insérée


def avoir_colonne_joueur(Symbole,Plateau_de_jeu): #MODIF : Exercice 4.5
    Insere = False
    while not(Insere):
        Colonne = 7
        while not(Colonne>=0 and Colonne<=6) :
            Colonne = int(input("N° de la colonne où insérer la pièce(1 à 7): "))-1
        if insertion_colonne_possible(Colonne,Plateau_de_jeu):
            Insere = True
        else:
            print("Insertion impossible!")
    Ligne = inserer_piece(Colonne,Symbole,Plateau_de_jeu)
    return Colonne,Ligne
#    Demande au joueur de couleur Symbole la colonne où insérer le pion 
#    dans le plateau de jeu, et l'insère si possible
#    Modif : retourne la colonne et la ligne où la pièce a été insérée


def verification_horizontale(Colonne,Ligne,Symbole,Plateau_de_jeu): #ORIGINAL
    Quatre_Aligne = False
    Recurrence = 0
    for indice in range(Colonne-3,Colonne+4):
        if (indice >= 0 and indice < len(Plateau_de_jeu[Ligne])):
            if (Plateau_de_jeu[Ligne][indice] == Symbole):
                Recurrence +=1
                if Recurrence == 4:
                    Quatre_Aligne = True
            else:
                Recurrence = 0
    return Quatre_Aligne
#    Vérifie si 4 pions sont alignés horizontalement ;
#    L'idée principale est de comparer pour un pion précis s'il est de
#    la couleur Symbole donné en paramètre
#    On applique cette vérification plusieurs fois, dans des bornes calculées
#    par rapport à la position de la colonne du pion donné en paramètre,
#    On empêche cependant à la vérification de s'effectuer en dehors de la ligne
#    La vérification s'effectue alors de la colonne-3 jusqu'à la colonne+3,
#    ainsi qu'à la colonne 0 minimum et la colonne 6 maximum
#    On défini alors une variable Récurrence comptant le nombre de vérification
#    vraie, et cette variable passe la vérification globale horizontale vraie
#    s'il elle a été compté vraie au moins 4 fois d'affilé


def verification_verticale(Colonne,Ligne,Symbole,Plateau_de_jeu): #ORIGINAL
    Quatre_Aligne = False
    Recurrence = 0
    for indice in range(Ligne-3,Ligne+4):
        if (indice >= 0 and indice < len(Plateau_de_jeu)):
            if (Plateau_de_jeu[indice][Colonne] == Symbole):
                Recurrence +=1
                if Recurrence == 4:
                    Quatre_Aligne = True
            else:
                Recurrence = 0
    return Quatre_Aligne
#    Vérifie si 4 pions sont alignés verticalement ;
#    L'idée principale est de comparer pour un pion précis si le pion
#    est de la couleur Symbole donné en paramètre
#    On applique cette vérifications plusieurs fois, dans des bornes calculées
#    par rapport à la position de la ligne du pion donné en paramètre
#    On empêche cependant à la vérification de s'effectuer en dehors de la colonne
#    La vérification s'effectue alors de la ligne-3 jusqu'à la ligne+3,
#    ainsi qu'à la ligne 1 minimum et la ligne 6 maximum
#    On défini alors une variable Récurrence comptant le nombre de vérification
#    vraie, et cette variable passe la vérification globale verticale vraie
#    s'il elle a été compté au moins 4 fois d'affilé

def verification_diagonale_hautegauche_basdroite(Colonne,Ligne,Symbole,Plateau_de_jeu): #ORIGINAL
    Quatre_Aligne = False
    Recurrence = 0
    for indice_Colonne in range(Colonne-3,Colonne+4):
        for indice_Ligne in range(Ligne-3,Ligne+4):
            if (indice_Colonne >= 0 and indice_Ligne >= 0 and indice_Ligne < len(Plateau_de_jeu) and indice_Colonne < len(Plateau_de_jeu[Ligne])):
                if indice_Ligne - indice_Colonne == Ligne - Colonne :
                    if (Plateau_de_jeu[indice_Ligne][indice_Colonne] == Symbole):
                        Recurrence +=1
                        if Recurrence == 4:
                            Quatre_Aligne = True
                    else :
                        Recurrence = 0
    return Quatre_Aligne
#    (Voir vérification_verticale ou vérification_horizontale)
#    Dans la même idée, on applique les deux principes de vérifications
#    horizontale et verticale pour cette vérification diagonale
#    Cependant on créé une abscisse diagonale dont la position du pion est
#    définie par sa position de ligne moins sa position de colonne,
#    et l'on empêche l'éxecution des vérifications si la position vérifiée
#    n'a pas le même abscisse diagonale que le pion
#    Les autres conditions de vérifications s'appliquent toujours
        

def verification_diagonale_basgauche_hautedroite(Colonne,Ligne,Symbole,Plateau_de_jeu): #ORIGINAL
    Quatre_Aligne = False
    Recurrence = 0 
    for indice_Colonne in range(Colonne-3,Colonne+4):
        for indice_Ligne in range(Ligne+3,Ligne-4,-1):
            if (indice_Colonne >= 0 and indice_Ligne >= 0 and indice_Ligne < len(Plateau_de_jeu) and indice_Colonne < len(Plateau_de_jeu[Ligne])):
                if ((len(Plateau_de_jeu)-1) - indice_Ligne - indice_Colonne) == ((len(Plateau_de_jeu)-1) - Ligne - Colonne):
                    if (Plateau_de_jeu[indice_Ligne][indice_Colonne] == Symbole):
                        Recurrence +=1
                        if Recurrence == 4:
                            Quatre_Aligne = True
                    else :
                        Recurrence = 0
    return Quatre_Aligne
#    (Voir vérification_diagonale_hautegauche_basdroite)
#    Ici, on utilise le même principe en changenant le sens de vérification
#    horizontal, et en modifiant l'abscisse diagonale dans son calcul ;
#    Celle-ci est calculé par la ligne maximum moins la position de ligne
#    moins la position de colonne
#    Le changement de sens de la vérification horizontale demande aussi un
#    changement des bornes minimum et maximum utilisées pour empêcher des
#    vérifications en dehors du tableau ; on vérifie alors de la colonne 0
#    à la colonne 6, et de la ligne 5 à la ligne 0


def a_le_joueur_gagne(Colonne,Ligne,Symbole,Plateau_de_jeu): #ORIGINAL, mais mention obligatoire dans 5.1
    Gagnant = False
    if (verification_verticale(Colonne,Ligne,Symbole,Plateau_de_jeu) or verification_horizontale(Colonne,Ligne,Symbole,Plateau_de_jeu) or verification_diagonale_basgauche_hautedroite(Colonne,Ligne,Symbole,Plateau_de_jeu) or verification_diagonale_hautegauche_basdroite(Colonne,Ligne,Symbole,Plateau_de_jeu)): #C'est long mais c'est pas compliqué à comprendre
        Gagnant = True
    return Gagnant
#    Retourne vraie si au moins l'une des vérifications est vraie
#    Note : même si elle n'est que mentionné, cette fonction est sensée ne
#    prendre en paramètre juste le Symbole du joueur et le Plateau de jeu


def Fonction_Principale_boum(): #MODIF : Exercice 5.1
    Plateau_Jeu = creer_plateau_jeu()
    Joueur1 = ' '
    Joueur2 = ' '
    while not(Joueur1 == 'R' or Joueur1 == 'J'):
        Joueur1 = input("Sélectionner votre couleur! (J : Jaune, R : Rouge) : ")
        if Joueur1 == 'R' :
            Joueur2 = 'J'
            print("Le Joueur 2 sera Jaune!")
        else:
            Joueur2 = 'R'
            print("Le Joueur 2 sera Rouge!")
    Tour = 0
    Tour_liste = [Joueur1,Joueur2]
    Gagne = [False,False]
    while (not (Gagne[0] or Gagne[1])) and (not jeu_plein(Plateau_Jeu)):
        recracher_plateau_jeu(Plateau_Jeu)
        Colonne,Ligne = avoir_colonne_joueur(Tour_liste[Tour%2],Plateau_Jeu)
        if a_le_joueur_gagne(Colonne,Ligne,Tour_liste[Tour%2],Plateau_Jeu):
            Gagne[Tour%2] = True
        Tour +=1
    recracher_plateau_jeu(Plateau_Jeu)
    if Gagne[0]:
        print("Le joueur 1 est gagnant, félicitations!")
    elif Gagne[1]:
        print("Le joueur 2 gagne, bien joué!")
    else:
        print("Jeu terminé, aucun gagnant!")
#    La fonction principale ;
#        1 - Construit le plateau de jeu
#        2 - Demande au joueur 1 sa couleur, et déduit la couleur du joueur 2
#        3 - Fait tourner la boucle du jeu :
#    
#    Tant que le plateau de jeu n'est pas plein, ou qu'aucun des deux joueurs 
#    n'a gagné, via une liste de variable gardant en mémoire la victoire 
#    du jJoueur1 et du Joueur2 indépendement, elle fait jouer au tour à tour 
#    chaques joueurs par l'utilisation d'une variable Tour qu'on calcule en 
#    retenant le reste de sa divison par 2
#    Modif : la fonction appelée a_le_joueur_gagne ne devrait prendre en
#    paramètre que la couleur du joueur S et le plateau de jeu P ;
#    
#    Il est probable que cette fonction ai été pensé pour ne jamais avoir
#    d'informations à propos de la ligne et colonne où le pion est situé,
#    et que les fonctions de vérifications soit programmées de telle sorte
#    qu'elles scanneraient le plateau de jeu en entier, ce n'est cependant
#    pas de cette manière que j'ai écrit ces fonctions là, dans un soucis
#    d'optimisation (on aurai eu besoin de scanner toutes les lignes pour
#    la vérification horizontale, et toutes les colonnes pour la vérification
#    verticale, ce qui n'est pas le cas avec ce code)

