tableau=[1,1,0,0,1,0,0,0,1]
grpe_nul=0
for compteur in range(len(tableau)) :
    if tableau[compteur]==0 :
        grpe_nul+=1
    else :
        grpe_nul_maxi,grpe_nul=grpe_nul,0
print("Le plus long groupe d'éléments nuls est de",grpe_nul_maxi)
