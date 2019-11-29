jour=int(input("Entrer le numéro de jour : "))
mois=int(input("Entrer numéro de mois : "))
annee=int(input("Entrer le numéro d'année : "))

if jour<29 and mois==2 :
    date_valide=True
elif jour<30 and mois==2 and (annee%4==0 or (annee%4==0 and annee%100==0 and annee%400==0)) :
    date_valide=True
elif jour<31 and (mois==4 or mois==6 or mois==9 or mois==11) :
    date_valide=True
elif jour<32 and (mois==1 or mois==3 or mois==5 or mois==7 or mois==8 or mois==10 or mois==12) :
    date_valide=True
else :
    date_valide=False

if len(jour)=1 :
    jour_str=str("0"+str(jour))
else :
    jour_str=str(jour)

if len(mois)=1 :
    mois_str=str("0"+str(mois))

if date_valide :
    print("La date est le : "+jour_str+"/""+mois_str+"/"+str(annee))
else :
    print("La date est invalide")
