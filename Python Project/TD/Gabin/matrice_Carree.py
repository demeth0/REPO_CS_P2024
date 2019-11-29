matrice=
erreur=False
nbr_ligne=len(matrice)
nbr_colonnes=len(matrice[0]])
for compteur1 in range(nbr_lignes) :
    for compteur2 in range(1,nbr_colonnes) :
        if matrice[compteur2][compteur1]!=matrice[compteur1][compteur2] :
            erreur=True
