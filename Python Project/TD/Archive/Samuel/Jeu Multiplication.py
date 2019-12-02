# -*- coding: utf-8 -*-
"""
Spyder Editor

"""
    
def jeu_de_la_multiplication():
    table_number = 0
    number_is_valid = False
    while number_is_valid == False:
        input_result = input("rentrez un nombre entre 2 et 9 pour que le jeu commence\ntable : ")
        try :
            table_number = int(input_result)
            number_is_valid = True
        except ValueError : 
            number_is_valid = False
    nb_erreur = 0
    for multiplier in range(1, 10) :
        input_answer_text = str(multiplier)+"*"+str(table_number)+"="
        input_answer = input(input_answer_text)
        answer = 0
        try :
            answer = int(input_answer)
        except ValueError : 
            print("=> FAUX, la bonne réponse est:"+str(multiplier*table_number))
            nb_erreur = nb_erreur +1
            continue
        if answer == multiplier * table_number :
            print("juste")
        else:
            nb_erreur = nb_erreur+1
            print("=> FAUX, la bonne réponse est:"+str(multiplier*table_number))
    print("nombre d'erreur :"+str(nb_erreur))
    if nb_erreur == 0 :
        print("FELICITATION")