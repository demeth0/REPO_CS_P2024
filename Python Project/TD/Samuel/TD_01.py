# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
"""
(feuille 1)
PGCD
factoriel
jeu multi
->tableau et multiplication(feuille 2)
hamming
grp_null_maxi
"""

def PGCD(a, b):
    _r = 0
    _a = a
    _b = b
    while(_b != 0):
        _r = _a%_b
        _a = _b
        _b = _r
    print(_a)
    
#suite de fibonacci
def fibonacci(n):
    f0 = 0
    f1 =1
    fi = 0
    if(n == 1):
        fi = f1
    
    for i in range(2, n+1):
        fi = f0 +f1
        f0 = f1
        f1 = fi
    print(fi)
    
def factoriel(n):
    n_total = 1
    for i in range(1, n+1):
        n_total = n_total * i
        
    print(n_total)
    
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

def Hamming(tab_a, tab_b):
    diff = 0
    for i in range(len(tab_a)):
        if(tab_a[i] != tab_b[i]):
            diff = diff+1
    return diff

def grp_nul_maxi(tab_bin):
    max_size_nul_value_tab = 0
    cur_tab_nul_value = 0
    for i in tab_bin:
        if(i == 0):
            cur_tab_nul_value = cur_tab_nul_value+1
        else:
            if cur_tab_nul_value > max_size_nul_value_tab :
                max_size_nul_value_tab = cur_tab_nul_value
            cur_tab_nul_value = 0
    return max_size_nul_value_tab
    