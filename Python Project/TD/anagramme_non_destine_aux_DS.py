#Ce programme fonctionne mais utilise la fonction list.sort
#list.sort est une fonction de base de python mais quasi-exclusive à python
#Par conséquent, les profs vont voir flou si vous mettez ça dans une copie, donc le recopiez pas tel quel
mot1=input("Entrer le premier mot : ")
mot2=input("Entrer le deuxieme mot : ")
if len(mot1)==len(mot2) :
    mot1_list=list(mot1.lower())
    mot2_list=list(mot2.lower())
    mot1_list.sort()
    mot2_list.sort()
    if mot1_list==mot2_list :
        print(mot1,"et",mot2,"sont des annagrames")
    else :
        print(mot1,"et",mot2,"ne sont pas des annagrames")
else :
    print(mot1,"et",mot2,"ne sont pas de la même longueur et ne peuvent pas être des annagrames")
