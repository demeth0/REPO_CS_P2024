

annee = int(input ("Veuillez entrer une année :"))
def bissextilite (annee) :
    bissextilite1 = annee%4
    bissextilite2 = annee%100
    bissextilite3 = annee%400
    if (bissextilite1 == 0 and (bissextilite2 !=0 or (bissextilite2 == 0 and bissextilite3 == 0))) :
        print ("L'année est bissextile")
    else:
        print("L'annee n'est pas bissextille")
bissextilite (annee)
