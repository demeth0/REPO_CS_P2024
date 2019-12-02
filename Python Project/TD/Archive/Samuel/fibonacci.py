# -*- coding: utf-8 -*-
"""
Spyder Editor

"""
    
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
    
