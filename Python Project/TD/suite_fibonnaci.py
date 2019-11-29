print ("F0 = 0")
print ("F1 = 1")
Fn = 1
rang = input("Veuillez saisir un terme de rang n>=2 et l'algorithme vous le calculera selon la suite de Fibonnaci : ")
rang1=int(rang)
i=3
compteur = int(i)
for compteur in range(rang1-2):
    Fn_2 = Fn
    Fn = Fn-2+Fn-1
    print("Le terme au rang ",i,"est :",Fn)
    i = i + 1
    compteur = compteur + 1
