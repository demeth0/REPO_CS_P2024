monnaie=[2,1,0.5,0.2,0.1,0.05,0.02,0.01]
somme_Donnee=float(input("Valeur de la somme donnée en euros"))
valeur_Achat=float(input("Valeur de l'achat en euros"))
somme_A_Rendre=somme_Donnee-valeur_Achat
if somme_A_Rendre>0:
    for piece in range(len(monnaie)):
        somme_Deja_Rendue=int(somme_A_Rendre//monnaie[piece])
        if somme_Deja_Rendue!=0:
            print("Il faut rendre "+str(somme_Deja_Rendue)+" pièces de "+str(monnaie[piece])+" euros")
            somme_A_Rendre=somme_A_Rendre%monnaie[piece]
else:
    if somme_A_Rendre==0:
        print("Le compte est bon")
    else:
        print("La somme donnée est insuffisante")
