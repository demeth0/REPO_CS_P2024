vSeuil=7.41
pSeuil=2.3
volume=float(input("Volume : "))
pression=float(input("Pression : "))
if volume<=vSeuil and pression<=pSeuil :
    print ("Tout va bien")
elif pression>pSeuil and volume<=vSeuil :
    print("Augmentation du volume de l'enceinte")
elif volume>vSeuil and pression <= pSeuil :
    print("Diminution du volume de l'enceinte")
else :
    print("Arrêt immédiat")
