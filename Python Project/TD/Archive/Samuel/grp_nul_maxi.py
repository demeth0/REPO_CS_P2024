# -*- coding: utf-8 -*-
"""
Spyder Editor

"""

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
    