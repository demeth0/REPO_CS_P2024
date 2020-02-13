# -*- coding: utf-8 -*-
"""
Created on Thu Feb 13 19:00:12 2020

@author: Samuel Dechambre
"""


#tri fusion
def sorting(value_list):
    
    #merge the two tabs by placing the element one per one of each list by order to one list
    def merge_and_sort(value_list_1, value_list_2):
        result_list = []
        index_list_1 = 0
        index_list_2 = 0
        while index_list_1 < len(value_list_1) or index_list_2 < len(value_list_2) :
            #si l'une des liste a deja etait completement ajouter on ajoute le reste de l'autre
            if index_list_1 >= len(value_list_1) :
                result_list += value_list_2[index_list_2:]
                index_list_2 = len(value_list_2)
                #arreter la boucle
            elif index_list_2 >= len(value_list_2) :
                result_list += value_list_1[index_list_1:]
                index_list_1 = len(value_list_1)
            else:
                if value_list_1[index_list_1] <= value_list_2[index_list_2]:
                    result_list += [value_list_1[index_list_1]]
                    index_list_1 +=1
                else:
                    result_list += [value_list_2[index_list_2]]
                    index_list_2+=1
        return result_list
    
    def merge_table_2p2(list_value_list):
        list_order_2 = []
        i = 0
        while i < len(list_value_list):
            if i+1 < len(list_value_list):
                list_order_2 += [merge_and_sort(list_value_list[i], list_value_list[i+1])]
                i += 2
            else:
                list_order_2 += [list_value_list[i]]
                i+=1
        return list_order_2
    
    
    #transformation en singleton
    result_value_list = [[i] for i in value_list]
    while len(result_value_list) >1 :
        result_value_list = merge_table_2p2(result_value_list)
    return result_value_list
    
    