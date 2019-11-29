nombre_1=int(input("Entrer le premier nombre : "))
nombre_2=int(input("Entrer le second nombre : "))
reste=1

while reste!=0 :
    if nombre_1<nombre_2 :
        number_switch=nombre_1
        nombre_1=nombre_2
        nombre_2=number_switch
    reste=nombre_1%nombre_2
    if nombre_1<nombre_2 :
        nombre_2=reste
        pgcd=nombre_1
    else :
        nombre_1=reste
        pgcd=nombre_2

print(pgcd)
