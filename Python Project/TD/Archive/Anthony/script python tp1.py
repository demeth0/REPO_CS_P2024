# -*- coding: utf-8 -*-
"""
Éditeur de Spyder

Ceci est un script temporaire.
"""

"""
                A) MANIPULATION DE SOMME
"""
#1) :
    
#8.5/2.5 = 3.+
#8/2=4

float_8over5 = 8.5/2.5
int_8 = int(8.5)
int_5 = int(2.5)
int_8over5 = int(float_8over5)
bool_comparer = int_8over5 == int_8/int_5
print(bool_comparer)

#2) :
    
print(1.5+1.5,"\n")
print(1.5-1,"\n")
print(3.*7,"\n")
#      (1-2).,"\n",   
"""                 
(1-2).,"\n",
      ^
SyntaxError: invalid syntax
"""
#      .5-.3,"\n",
"""
    .5-.3,"\n",
     ^
SyntaxError: invalid syntax
"""     
#      4/(9-3**2),"\n",
"""
    4/(9-3**2),"\n",

ZeroDivisionError: division by zero
"""
print(float(7//12),"\n")

#3) :
    
"""
le contenu de x va dans z
le contenu de y va dans x
le contenu de z va dans y
"""
def changer_variable(_x,_y,_z):
    #we save the value of z in a temp value for future uses
    _z_temp = z
    _z=x
    _x=y
    _y=_z_temp
    print("x=",_x,"\ny=",_y,"\nz=",_z)
x=1
y=2
z=3
changer_variable(x,y,z)



"""
b)retours sur les algo vu en td
"""

def conversion_franc_euros(_francs_a_convertir):
    _euros =_francs_a_convertir/6.55957
    _euro_arrondis = float(int(_euros*100))/100.0
    return _euro_arrondis
    
francs_a_convertir = float(input("Veuillez entrer la somme en francs a convertir en euros\n")) 

print("La somme convertie est de " ,conversion_franc_euros(francs_a_convertir),"euros")   
    

"""
retourne la somme d'argent a rendre en nombre de piece de 1 centime
"""
def rendre_monnaie_centime(_monnaie_a_rendre_euro) :
    _int_monnaie_a_rendre_centime = int(_monnaie_a_rendre_euro *100)
    return _int_monnaie_a_rendre_centime
    
    
argent_a_rendre_euro = float(input("monnaie a rendre en euros \n") )

print(rendre_monnaie_centime(argent_a_rendre_euro), " centimes")
"""
c) autres algorithmes    
"""

def conversion_to_jours_heure_minutes_seconde(seconde):
    #on transmorme des secondes en minute et seconde    
    nb_seconde_reste = seconde % 60
    nb_minutes = seconde // 60
        
    #on transmorme des minutes en heure et minute
    nb_heure = nb_minutes //60
    nb_minute_reste = nb_minutes%60
        
    #on transmorme des heures en jour et heures
    nb_jour = nb_heure //24
    nb_heure_reste = nb_heure%24
         
    print(nb_jour,", ",nb_heure_reste, ", ",nb_minute_reste, ", ", nb_seconde_reste)
    
    
conversion_to_jours_heure_minutes_seconde(309639)
