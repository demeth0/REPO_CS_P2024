#une annee est dite bisextile si
"""
- si l'année est divisible par 4 et non divisible par 100, ou
- si l'année est divisible par 400.
"""
annee=int(input("Entrer une année : "))
if (annee%400==0) or (annee%4==0 and annee%100!=0) :
    print("C'est une année bissextile")
else :
    print("Ce n'est pas une année bissextile")
