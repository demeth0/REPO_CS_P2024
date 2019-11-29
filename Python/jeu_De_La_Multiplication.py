#Par rapport à la consigne, cette version du programme dit
#aussi a l'utilisateur pour quelles valeurs il s'est trompé
table=int(input("Entrer la table à reciter : "))

while table<2 or table>9 :
    table=int(input("La table doit être comprise en 2 et 9 : "))

erreurs=0
valeur_erreurs=[]

for compteur_table in range(11) :
    resultat_humain=int(input(str(compteur_table)+"x"+str(table)+"="))
    resultat_machine=table*compteur_table
    if resultat_humain!=resultat_machine :
        erreurs+=1
        valeur_erreurs.append(compteur_table)

if erreurs==0 :
    print("C'est un sans-fautes, bravo !")
else :
    print("Vous avez fait une ou des erreurs pour "+str(valeur_erreurs))
    print("Les bonnes reponses étaient :")
    for compteur_erreurs in range(len(valeur_erreurs)) :
        resultat_erreurs=valeur_erreurs[compteur_erreurs]*table
        print(str(valeur_erreurs[compteur_erreurs])+"x"+str(table)+"="+str(resultat_erreurs))
