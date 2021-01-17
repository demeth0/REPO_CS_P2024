# -*- coding: utf-8 -*-
"""
Created on Sun Dec  8 20:45:59 2019

@author: Samuel Dechambre
"""
COVERED_STAT = 0
DISCOVERED_STAT = 1
MINED_STAT = 2
FLAGGED_STAT = 3

class Case(object):
    __contain_mine = None
    __discovered = None
    __flagged = None
    __number_mine_around = 0
    __statue = 0
    
    def __init__(self):
        self.__contain_mine = False
        self.__discovered = False
        self.__flagged = False
        self.__generateStatue()
        
    def hasMine(self):
        return self.__contain_mine
    #return if the operation success (if the case isn't discovered)
    def setMine(self):
        if not self.__discovered :
            self.__contain_mine = True
            self.__generateStatue()
        return not self.__discovered
    
    #return if the operation success (if the case isn't discovered)
    def unsetMine(self):
        if not self.__discovered :
            self.__contain_mine = False
            self.__generateStatue()
        return not self.__discovered
        
    def discover(self):
        if not self.__flagged :
            self.__discovered = True
            self.__generateStatue()
        
    def isDiscovered(self):
        return self.__discovered
    
    def flag(self):
        if not self.__discovered :
            self.__flagged = True
            self.__generateStatue()
    def unflag(self):
        if not self.__discovered :
            self.__flagged = False
            self.__generateStatue()
    def isFlagged(self):
        return self.__flagged
    
    def addMineToNumberOfMineAround(self):
        self.__number_mine_around += 1 
    
    def getNumberOfMineAroud(self):
        return self.__number_mine_around
    
    #0:covered     1:discovered       2:discovered(bomb)      3:flagged
    #if the case is brocken it will return -1
    #to let the system know that we need to change the texture type of the case
    def __generateStatue(self):
        int_state = 0
        if self.isDiscovered() :
            if self.hasMine():
                int_state = MINED_STAT
            else:
                int_state = DISCOVERED_STAT
        else:
            if self.isFlagged() :
                int_state = FLAGGED_STAT
            else :
                int_state = COVERED_STAT
                
        self.__statue = int_state
        
    def getStat(self):
        return self.__statue
    
        
        
        
        