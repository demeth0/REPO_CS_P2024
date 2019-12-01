tableau1=[0,1,0,1]
tableau2=[1,1,0,0]
distance=0
for compteur in range(len(tableau1)) :
    if tableau1[compteur]!=tableau2[compteur] :
        distance+=1
print("La distance de Hamming entre les deux tableaux est de",distance)
