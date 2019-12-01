def fevrier_bissextile (jour_test,mois_test,annee_test) :
    return (jour_test<30 and mois_test==2 and ((annee_test%4==0 and annee_test%100!=0) or (annee_test%100==0 and annee_test%400==0)))

mois_A_31=[1,3,5,7,8,10,12]
mois_A_30=[4,6,9,11]

jour=int(input("Entrer le numéro de jour : "))
mois=int(input("Entrer numéro de mois : "))
annee=int(input("Entrer le numéro d'année : "))

if jour<29 and mois==2 :
    date_valide=True
elif fevrier_bissextile(jour,mois,annee) :
    date_valide=True
elif jour<31 and (mois in mois_A_30) :
    date_valide=True
elif jour<32 and (mois in mois_A_31) :
    date_valide=True
else :
    date_valide=False

if len(str(jour))==1 :
    jour_str=str("0"+str(jour))
else :
    jour_str=str(jour)

if len(str(mois))==1 :
    mois_str=str("0"+str(mois))

if date_valide :
    print("La date est le : "+jour_str+"/"+mois_str+"/"+str(annee))
else :
    print("La date est invalide")
