#Ce programme fonctionne avec la recursivité
#C'est la méthode attendue mais pas la meilleure
#En calculant avec une boucle for et en addtionant à chaque itération,
#le programme est plus lisible et prend moins de mémoire puisqu'en récursivité,
#la machine doit garder tous les resultats en mémoire avant de calculer
rang=int(input("Entrer le nombre à calculer : "))

def factorielle_Recursive(rang) :
    if rang==1 :
        nombre_A_Retourner=1
    else :
        nombre_A_Retourner=rang*int(factorielle_Recursive(rang-1))
    return nombre_A_Retourner

print(rang,"!","=",factorielle_Recursive(rang))
