#Ce programme est juste mais surement un peu compliqué à comprendre
#Les noms de variables ne doivent pas être très claires
var_1=0
var_2=1

rang_Max=int(input("Donner le rang : "))

print(var_1)
print(var_2)

for n in range(rang_Max-1) :
    resultat=var_1+var_2
    print(resultat)
    var_1=var_2
    var_2=resultat
