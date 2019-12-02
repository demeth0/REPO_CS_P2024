sexe=input("Homme (entrer 1) ou Femme (entrer 2) ? : ")
if sexe==2 :
    statut=input("Mariée (entrer 1) ou pas mariée (entrer 2) ? : ")

if sexe=="1" :
    print("Bonjour Monsieur")
elif sexe=="2" and statut=="1" :
    print("Bonjour Madame")
elif sexe=="2" and statut=="2" :
    print("Bonjour Mademoiselle")
else :
    print("Error")
