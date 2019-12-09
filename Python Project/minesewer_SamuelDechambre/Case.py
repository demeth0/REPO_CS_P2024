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
    contain_mine = None
    discovered = None
    flagged = None
    number_mine_around = None
    statue = None
    
    def __init__(self, contain_mine = False):
        self.contain_mine = contain_mine
        self.discovered = False
        self.flagged = False
        self.number_mine_around = 0
        self.statue = 0
        
    def hasMine(self):
        return self.contain_mine
    #return if the operation success (if the case isn't discovered)
    def setMine(self):
        if not self.discovered :
            self.contain_mine = True
        return not self.discovered
    
    #return if the operation success (if the case isn't discovered)
    def unsetMine(self):
        if not self.discovered :
            self.contain_mine = False
        return not self.discovered
        
    def discover(self):
        if not self.flagged :
            self.discovered = True
        
    def isDiscovered(self):
        return self.discovered
    
    def flag(self):
        if not self.discovered :
            self.flagged = True
    def unflag(self):
        if not self.discovered :
            self.flagged = False
    def isFlagged(self):
        return self.flagged
    
    def addMineToNumberOfMineAround(self):
        self.number_mine_around += 1 
    
    def getNumberOfMineAroud(self):
        return self.number_mine_around
    
    #0:covered     1:discovered       2:discovered(bomb)      3:flagged
    #if the case is brocken it will return -1
    #to let the system know that we need to change the texture type of the case
    def generateStatue(self):
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
                
        self.statue = int_state
        
    def getStat(self):
        return self.statue
    
        
        
        
        