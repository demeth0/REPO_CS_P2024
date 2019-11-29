
def conversion_to_euro () :
    print("\nVeuillez entrer la somme en franc a convertir en euros\n");
    Somme_en_franc = input()
    print ("la somme en franc est de ",Somme_en_franc)
    euro_ = float(Somme_en_franc)
    euro = euro_ / 6.55957
    euro = round(2)
    print('la somme converti est de',str(euro),"€")

conversion_to_euro()
