# -*- coding: utf-8 -*-
"""
Created on Sun Dec  8 19:44:11 2019

Version 2

@author: Samuel Dechambre
"""

"""
données a reset en debut de nouvelles partie :
    matrice case
    row size
    column size
    mine_number
    first clck boolean


"""

import tkinter
from random import randint as getRandInt

from lib.matrice import create as create_matrice

import Case
import minesewer_config as Data

class WinApp(tkinter.Frame):
    
    #start int
    mine_number = None                                               #
    case_row_size = None                                             #
        #the number of case in row                                   #  game data to 
    case_column_size = None                                          #  reset if
        #the number of case in column                                #  if you want to start a 
                                                                     #  new game
    #condition if true initialize mines (place randomly)             #
    firstClick = True                                                #
    
    #the positions of the eyes used to move the gameboard with mouse drag
    x_view_pos = None
    y_view_pos = None
    last_x_mouse_pos = None
    last_y_mouse_pos = None
    #end int
    
    #start images                 IMAGES RESSOURCES
    img_mine_case = None
    img_covered_case = None
    img_discovered_case = None
    img_flagged_case = None
    img_discovered_case_tagged = None
    #end images
    
    #tkinter widget             MAIN FRAME COMPONENT
    gameBoard_canvas = None
    discoverAllButton = None
    unflagAllButton = None
    
    #matrice lib object          cases matrice of the size (case_row_size,case_column_size)
    gameboard_matrice = None
    

    
    
    def __init__(self, row = 0, column = 0, mines = 0, master = None):
        #frame init
        tkinter.Frame.__init__(self, master)
        self.pack()
        
        
        #constructor init
        self.case_column_size = column
        self.case_row_size = row
        self.mine_number = mines
        
        #create an empty matrice can't create case here because of pointer issues
        self.gameboard_matrice = create_matrice(self.case_row_size, self.case_column_size, None) 
        
        #the default position of the board in the frame upper-left corner
        self.x_view_pos = 0
        self.y_view_pos = 0
        
        #image ressource init
        self.img_mine_case = tkinter.PhotoImage(file=Data.EXTERNAL_RES_FILE_PATH+Data.RES_MINE_CASE)
        self.img_flagged_case = tkinter.PhotoImage(file=Data.EXTERNAL_RES_FILE_PATH+Data.RES_FLAGGED_CASE)
        #useless because already created in the img_discovered_case_tagged[0]
        #self.img_discovered_case = tkinter.PhotoImage(file=EXTERNAL_RES_FILE_PATH+RES_DISCOVERED_CASE)
        self.img_covered_case = tkinter.PhotoImage(file=Data.EXTERNAL_RES_FILE_PATH+Data.RES_COVERED_CASE)
        
        #the position in the tab represent the number to print in function of the mine number around the case (bijective)
        self.img_discovered_case_tagged = []
        for path in Data.RES_DISCOVERED_CASE_TAGGED :
            self.img_discovered_case_tagged = self.img_discovered_case_tagged+[tkinter.PhotoImage(file=Data.EXTERNAL_RES_FILE_PATH+path)]
        
        #fill the matrice with default cases and will choose aleatory mined case after first click to prevent instant losses
        #init cases just reading the full matrice
        for i in range(self.case_row_size):
            for j in range(self.case_column_size) :
                self.gameboard_matrice[i][j] = Case.Case()
        
        #create frame component (for now only the gameborad canvas)
        self.createWidget(master)
        
        self.gameBoard_canvas.focus_set()
        
        #binding function to keyboard action or mouse action
        #Button 1 == "left_click" and Button 3 == "right_click"
        if Data.KEY_DISCOVER == '<ButtonRelease-1>' :
            self.gameBoard_canvas.bind('<ButtonRelease-1>', self.mouse_release_with_discover)
        else :
            self.gameBoard_canvas.bind(Data.KEY_DISCOVER, self.discover)
            self.gameBoard_canvas.bind('<ButtonRelease-1>', self.mouse_release)
            
        self.gameBoard_canvas.bind('<B1-Motion>', self.mouse_motion_button_1)
        
        self.gameBoard_canvas.bind(Data.KEY_FLAG, self.flagCase)
        self.refresh()
        
    #need to pass the master in parameter because he is needed for creating the comps
    def createWidget(self,  master=None):
        self.gameBoard_canvas = tkinter.Canvas(self, width=Data.BOARD_WIDTH, height=Data.BOARD_HEIGHT, bg=Data.BOARD_BACKGROUND)
        self.gameBoard_canvas.pack({"side":"left"})
        self.subFrame = tkinter.Frame(self, width=Data.BOARD_MENU_WIDTH)
        self.subFrame.pack({"side":"left", "fill":"y"})
        
        self.label0 = tkinter.Label(self.subFrame, text="Menu")
        self.label0.pack({"fill":"y"})
        
        self.label1 = tkinter.Label(self.subFrame, text="Row")
        self.label1.pack({"fill":"y"})
        self.entry1 = tkinter.Entry(self.subFrame)
        self.entry1.pack({"fill":"y"})
        
        self.label2 = tkinter.Label(self.subFrame, text="Column")
        self.label2.pack({"fill":"y"})
        self.entry2 = tkinter.Entry(self.subFrame)
        self.entry2.pack({"fill":"y"})
        
        self.label3 = tkinter.Label(self.subFrame, text="Mine")
        self.label3.pack({"fill":"y"})
        self.entry3 = tkinter.Entry(self.subFrame)
        self.entry3.pack({"fill":"y"})
        
        self.discoverAllButton = tkinter.Button(self.subFrame, width=50, text="Discover All", command= self.discoverAll )
        self.discoverAllButton.pack({"fill":"y"})
        self.unflagAllButton = tkinter.Button(self.subFrame, width=50, text="unflag All", command= self.unflagAll )
        self.unflagAllButton.pack({"fill":"y"})
        self.button3 = tkinter.Button(self.subFrame, width=50, text="apply modif")
        self.button3.pack({"fill":"y"})
        
    #discover all cases (debug function)
    def discoverAll(self):
        if self.firstClick :
            self.initMines()
        for row in self.gameboard_matrice : 
            for case in row : 
                case.discover()
                
    #unflag all cases (debug function)
    def unflagAll(self):
        for row in self.gameboard_matrice : 
            for case in row : 
                case.unflag()
        
    #method to call to redraw the canvas only call this one time because it will refresh each BOARD_REFRESH_RATE ms
    def refresh(self):
        #erasing all the content of the canvas to avoid overlays
        self.gameBoard_canvas.delete("all")
        #drawing cases and other
        self.drawCanvas()
        #optimised method by tkinter to refresh the canvas without too many perf lost
        self.gameBoard_canvas.after(Data.BOARD_REFRESH_RATE, self.refresh)
        
    #sub method to refresh ,do not call this alone @see canvas.delete("all")
    def drawCanvas(self):
        #--------------- for each case
        for row in range(self.case_row_size):
            for column in range(self.case_column_size):
                # ----------------
                #calculating the case pos in function to the grid pos , the case pos
                #and the case width
                case_x_pos = self.x_view_pos+Data.SIZE_X_VECTOR*row
                case_y_pos = self.y_view_pos+Data.SIZE_Y_VECTOR*column
                
                #if the case is out of the screen
                if (case_x_pos+30 < 0 or case_y_pos+30 < 0) or (case_x_pos > Data.BOARD_WIDTH or case_y_pos > Data.BOARD_HEIGHT) :
                    continue
                
                #        DRAWING IMAGE IN FUNCTION TO THE CASE STATUE
                #0:covered     1:discovered       2:discovered(bomb)      3:flagged
                case = self.gameboard_matrice[row][column]
                #if statue not initialized will draw a covered case
                stat = case.getStat()
                if stat == Case.COVERED_STAT :
                    self.gameBoard_canvas.create_image(case_x_pos, case_y_pos, image = self.img_covered_case,anchor=tkinter.NW)
                elif stat == Case.DISCOVERED_STAT :
                    self.gameBoard_canvas.create_image(case_x_pos, case_y_pos, image = self.img_discovered_case_tagged[case.getNumberOfMineAroud()],anchor=tkinter.NW)
                elif stat == Case.MINED_STAT:
                    self.gameBoard_canvas.create_image(case_x_pos, case_y_pos, image = self.img_mine_case,anchor=tkinter.NW)
                elif stat == Case.FLAGGED_STAT :
                    self.gameBoard_canvas.create_image(case_x_pos, case_y_pos, image = self.img_flagged_case,anchor=tkinter.NW)
                
                
                
                
    """
            DEPLACEMENT DU PLATEAU
    """
    
    #for moving the gameboard freely
    """
        when they are set to null that mean that the mouse hasn't moved since the left mouse button
        has been pressed.
    """
    

    def mouse_motion_button_1(self, event):
        #if the value are null then we will init them with the current mouse position
        if self.last_y_mouse_pos == None or self.last_x_mouse_pos == None :
            self.last_x_mouse_pos = event.x
            self.last_y_mouse_pos = event.y
            return 
        #else we will calculate the motion from the last pos and move the gameboard in consequences
        else:
            #calculate pos differences
            x_motion = self.last_x_mouse_pos - event.x
            y_motion = self.last_y_mouse_pos - event.y
            #reinit the last mouse pos
            self.last_x_mouse_pos = event.x
            self.last_y_mouse_pos = event.y
            #changing the gameboard position in consequences
            self.x_view_pos -= x_motion
            self.y_view_pos -= y_motion
        
    #triggered when player release left mouse button
    def mouse_release(self, event):            
        #set the last mouse pos to None because we don't want to use this mouse pos because if we move the mouse elsewhere ad 
        #click again it will calculate the space between and will fuck up the pos of the game board
        self.last_x_mouse_pos = None
        self.last_y_mouse_pos = None
        
    def mouse_release_with_discover(self, event):
        self.discover(event)
        self.mouse_release(event)
    
    def discover(self, event):
        #to verify that we are not moving the plate at the same time
        if self.last_x_mouse_pos == None and self.last_y_mouse_pos == None :
            #send the coordinate to the discover function that will determine if there is a case here and if we can discover it or not
            self.discoverCase(event)
        
        
    """
           action function 
    """ 

    #discover the supposed case at the coordonate in args
    def discoverCase(self, event):
        #calculate x and y pos of the mouse relatively to the gameboard upper left case
        case_row = (event.x-self.x_view_pos)/Data.SIZE_X_VECTOR
        case_column = (event.y-self.y_view_pos)/Data.SIZE_Y_VECTOR
        #if has click in the grid
        if (0<=case_row and case_row < self.case_row_size) and (0<=case_column and case_column < self.case_column_size ) :
            #get integer value to use in the bidimentional table
            #cast need to be done after if cond, elsewhere it will flour number in ]-1;0[ as 0
            #and break the hitbox (ugly)
            case_row = int(case_row)
            case_column = int(case_column)
            #get the case at the click pos
            case_to_discover = self.gameboard_matrice[case_row][case_column]
                    
            #discover the case see Case.py for more details
            case_to_discover.discover()
            
            #init mines at first click
            if self.firstClick :    
                self.initMines()   
                self.firstClick = False
                
            
            #important after mine init else it will discover all the map
            #because there is no mines
            #if the case we just clicked is not near a mine just discover the cases around
            #to save some useless click to the player
            if case_to_discover.getNumberOfMineAroud() == 0 and not case_to_discover.hasMine():
                #get the list of cases around the main case and positions
                case_to_discover_stack = self.getCaseAround(case_row, case_column)
                #while there is some to discover 
                while len(case_to_discover_stack)>0 :
                    #remove the case we will discover from the case to discover
                    new_case_to_discover = case_to_discover_stack.pop()
                    #discover the case ...
                    new_case_to_discover[0].discover()
                    
                    #delete the positions coordinate mapped at the same index in the other list
                    #and save them
                    new_case_pos = new_case_to_discover[1]
                    
                    #if the case we just discovered is also a case with no mines near 
                    #just discover the case around her
                    #it's translated by adding the case covered around her in the "to discover"
                    #list
                    if new_case_to_discover[0].getNumberOfMineAroud() == 0 and not new_case_to_discover[0].hasMine():
                        new_case_to_discover_stack = self.getCoveredCasesAround(new_case_pos[0], new_case_pos[1])
                        case_to_discover_stack += new_case_to_discover_stack
            
    """
    a function that will take in argument a case position and return the 3-8 case around her
    and mapped in the same order the positions ex :
        c1 c2 c3
        c4 d0 c5
        c6 c7 c8
        
    return [c1,c2,c3,c4,c5,c6,c7,c8] , [[x1, y1],[x2,y2]...]
    """
    def getCaseAround(self,case_row,case_column):
        #returned lists
        case_around = []
        
        #these lists will be used to know if the case we try to find is in the gameboard
        #to prevent ArrayOutOfBoundException
        row_range = range(self.case_row_size)
        column_range = range(self.case_column_size)
        
        #testing if the cases around exist
        for col in range(case_column-1, case_column+2) :
            for row in range(case_row-1, case_row+2) :
                if (col in column_range) and (row in row_range) and not (col == case_column and row == case_row):
                    case_around += [ [self.gameboard_matrice[row][col],(row, col)] ]
        return case_around
         
    #derived function of getCaseAround that will filter covered cases and discovered cases
    #and return only the covered ones
    def getCoveredCasesAround(self, case_row, case_column):
        result = []
        case_around = self.getCaseAround(case_row, case_column)
        for i in range(len(case_around)):
            if not case_around[i][0].isDiscovered():
                result += [case_around[i]]
        return result
    
    #flagging button / flag or unflag a covered case
    def flagCase(self, event):
        #same as discoverCase function
        row_pos = (event.x-self.x_view_pos)/Data.SIZE_X_VECTOR
        column_pos = (event.y-self.y_view_pos)/Data.SIZE_Y_VECTOR
        
        #if has click in the grid
        if (0<=row_pos and row_pos < self.case_row_size) and (0<=column_pos and column_pos < self.case_column_size ) :
            #getting the case at the mouse pos
            case_to_flag = self.gameboard_matrice[int(row_pos)][int(column_pos)]
            
            #flag or unflag @see Case.py
            if case_to_flag.isFlagged():
                case_to_flag.unflag()
            else:
                case_to_flag.flag()
                
                  
    def initMines(self):
        minePlaced = 0
        while(minePlaced < self.mine_number):
            #choosing a random row
            row_pos = getRandInt(0, self.case_row_size-1)
            #and a random column
            col_pos = getRandInt(0, self.case_column_size-1)
            #getting the case at the said positions
            case_to_set = self.gameboard_matrice[row_pos][col_pos]
            #if the case isn't already mined
            if not case_to_set.hasMine():
                #if we success in placing the mine just to check if the case choosen is not the case
                #we discovered for the init
                if case_to_set.setMine() :
                    #1 less mine to place
                    minePlaced += 1
                    #saying to the case around covered or discovered that we are a mine
                    #/!\ do not use getCoveredCasesAround -> if wew place a mine next to the case we
                    #clicked for the init she will print 0 but there is a mine next to her
                    cases_around_mine = self.getCaseAround(row_pos, col_pos)
                    for case in cases_around_mine :
                        case[0].addMineToNumberOfMineAround()

#tkinter init
root = tkinter.Tk()

app = WinApp(row = 20, column = 20, mines = 50, master = root)
#close button function
def _quit():
    print("app closed")
    root.destroy()
root.protocol("WM_DELETE_WINDOW", _quit)
#to maintain the frame
app.mainloop()
