import sys
Mon_tableau1 = []
Mon_tableau2 = []

for i in range (4):
    Mon_tableau1.append(int(input("Entrer une valeur en binaire qui completera le tableau 1 de taille 4 : ")))
    print(Mon_tableau1,"\n")
    
for j in range(4):
    Mon_tableau2.append(int(input("Entrer une valeur en binaire qui completera le tableau 2 de taille 4 : ")))
    print(Mon_tableau2,"\n")


for k in Mon_tableau1:
    if (k != 0 and k != 1) :
        print("Vous n'avez pas entrer les bonnes valeurs")
        sys.exit
print("Votre 1er tableau est alors : ",Mon_tableau1)
for l in Mon_tableau2:
    if (l != 0 and l != 1) :
        print("Vous n'avez pas entrer les bonnes valeurs")
        sys.exit
print("Votre 2ème tableau est alors : ",Mon_tableau2)

def distance_hamming (Mon_tableau1, Mon_tableau2) :
    distance = 0 
    for h,t in zip(Mon_tableau1, Mon_tableau2):
        if h!=t:
                distance +=1
                print("la distance de hamming est de", distance)
        else:
                print("la distance de hamming est inchangé")
        

    
    
if len(Mon_tableau1) == len (Mon_tableau2) :
    distance_hamming(Mon_tableau1, Mon_tableau2)
else:
    print("La distance de hamming ne marche que entre 2 tableaux de même taille")
