annee=int(input("Entrer une année : "))
if annee%4==0 or (annee%4==0 and annee%100==0 and annee%400==0) :
    print("C'est une année bissextile")
else :
    print("Ce n'est pas une année bissextile")
