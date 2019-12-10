# -*- coding: utf-8 -*-
"""
Created on Sun Dec  8 19:44:11 2019

@author: Samuel Dechambre
"""

import tkinter
from matrice import create as create_matrice
import Case
from random import randint as getRandInt


#FRAME_WIDTH = 700
#FRAME_HEIGHT = 500

#en ms
BOARD_REFRESH_RATE = int(1000/60)
BOARD_WIDTH = 500
BOARD_HEIGHT = 500
BOARD_BACKGROUND = "black"

CASE_WIDTH = 1
#if you want to change the scale of the canvas you also need to resize the textures
SIZE_X_VECTOR = 30
SIZE_Y_VECTOR = 30

#ressources
RES_MINE_CASE = "mine_case_x30.gif"
RES_COVERED_CASE = "covered_case_x30.gif"
#RES_DISCOVERED_CASE = "discovered_case_x30.gif"
RES_DISCOVERED_CASE_TAGGED = ["discovered_case_x30.gif",
                              "discovered_case_1_x30.gif",
                              "discovered_case_2_x30.gif",
                              "discovered_case_3_x30.gif",
                              "discovered_case_4_x30.gif",
                              "discovered_case_5_x30.gif",
                              "discovered_case_6_x30.gif",
                              "discovered_case_7_x30.gif",
                              "discovered_case_8_x30.gif"]
RES_FLAGGED_CASE = "flagged_case_x30.gif"

EXTERNAL_RES_FILE_PATH = "ressources\\"

class WinApp(tkinter.Frame):
    #start int
    mine_number = None
    row = None
    column = None
    case_numbre = None
    
    x_view_pos = None
    y_view_pos = None
    #end int
    
    #start images                 
    img_mine_case = None
    img_covered_case = None
    img_discovered_case = None
    img_flagged_case = None
    img_discovered_case_tagged = None
    #end images
    
    #tkinter.canvas
    gameBoard_canvas = None
    
    #matrice lib object
    gameboard_matrice = None
    
    def __init__(self, row = 0, column = 0, mines = 0, master = None):
        #frame init
        tkinter.Frame.__init__(self, master)
        self.pack()
        
        #constructor
        self.column = column
        self.row = row
        self.mine_number = mines
        self.case_number = self.row * self.column
        self.gameboard_matrice = create_matrice(self.row, self.column, None)
        self.x_view_pos = 0
        self.y_view_pos = 0
        
        #image ressource init
        self.img_mine_case = tkinter.PhotoImage(file=EXTERNAL_RES_FILE_PATH+RES_MINE_CASE)
        self.img_flagged_case = tkinter.PhotoImage(file=EXTERNAL_RES_FILE_PATH+RES_FLAGGED_CASE)
        #self.img_discovered_case = tkinter.PhotoImage(file=EXTERNAL_RES_FILE_PATH+RES_DISCOVERED_CASE)
        self.img_covered_case = tkinter.PhotoImage(file=EXTERNAL_RES_FILE_PATH+RES_COVERED_CASE)
        
        self.img_discovered_case_tagged = []
        for path in RES_DISCOVERED_CASE_TAGGED :
            self.img_discovered_case_tagged = self.img_discovered_case_tagged+[tkinter.PhotoImage(file=EXTERNAL_RES_FILE_PATH+path)]
        #init cases
        for i in range(self.row):
            for j in range(self.column) :
                self.gameboard_matrice[i][j] = Case.Case(contain_mine = False)
        
        #create frame component
        self.createWidget(master)
        
        
        self.gameBoard_canvas.bind('<B1-Motion>', self.mouse_motion)
        self.gameBoard_canvas.bind('<ButtonRelease-1>', self.mouse_release)
        self.gameBoard_canvas.bind('<Button-3>', self.flagCase)
        self.refresh()
        
    def createWidget(self,  master=None):
        self.gameBoard_canvas = tkinter.Canvas(master, width=BOARD_WIDTH, height=BOARD_HEIGHT, bg=BOARD_BACKGROUND)
        self.gameBoard_canvas.pack({"side":"left"})
    def refresh(self):
        self.gameBoard_canvas.delete("all")
        self.drawCanvas()
        self.gameBoard_canvas.after(int(1000/60), self.refresh)
        #print("refreshing !")
        
    def drawCanvas(self):
        for row in range(self.row):
            for column in range(self.column):
                case_x_pos = self.x_view_pos+SIZE_X_VECTOR*row
                case_y_pos = self.y_view_pos+SIZE_Y_VECTOR*column
                
                #if the case is out of the screen
                if (case_x_pos+30 < 0 or case_y_pos+30 < 0) or (case_x_pos > BOARD_WIDTH or case_y_pos > BOARD_HEIGHT) :
                    continue
                
                #x = i and y = j        DRAWING IMAGE IN FUNCTION TO THE CASE STATUE
                #0:covered     1:discovered       2:discovered(bomb)      3:flagged
                case = self.gameboard_matrice[row][column]
                stat = case.getStat()
                if stat == Case.COVERED_STAT :
                    self.gameBoard_canvas.create_image(case_x_pos, case_y_pos, image = self.img_covered_case,anchor=tkinter.NW)
                elif stat == Case.DISCOVERED_STAT :
                    self.gameBoard_canvas.create_image(case_x_pos, case_y_pos, image = self.img_discovered_case_tagged[case.number_mine_around],anchor=tkinter.NW)
                elif stat == Case.MINED_STAT:
                    self.gameBoard_canvas.create_image(case_x_pos, case_y_pos, image = self.img_mine_case,anchor=tkinter.NW)
                elif stat == Case.FLAGGED_STAT :
                    self.gameBoard_canvas.create_image(case_x_pos, case_y_pos, image = self.img_flagged_case,anchor=tkinter.NW)
                
                
                
                
    """
            DEPLACEMENT DU PLATEAU
    """
    
    #for moving the gameboard freely
    last_x_mouse_pos = None
    last_y_mouse_pos = None
    def mouse_motion(self, event):
        if self.last_y_mouse_pos == None or self.last_x_mouse_pos == None :
            self.last_x_mouse_pos = event.x
            self.last_y_mouse_pos = event.y
            return 
        else:
            x_motion = self.last_x_mouse_pos - event.x
            y_motion = self.last_y_mouse_pos - event.y
            self.last_x_mouse_pos = event.x
            self.last_y_mouse_pos = event.y
            self.x_view_pos -= x_motion
            self.y_view_pos -= y_motion
        
        
        
    def mouse_release(self, event):
        
        #if there was no motion -> between two click releasse no motion that mean that last pos var havn(t been initialized)
        if self.last_x_mouse_pos == None and self.last_y_mouse_pos == None :
            row_pos = (event.x-self.x_view_pos)/SIZE_X_VECTOR
            column_pos = (event.y-self.y_view_pos)/SIZE_Y_VECTOR
            self.discoverCase(row_pos, column_pos)
            
        self.last_x_mouse_pos = None
        self.last_y_mouse_pos = None
        
        
        
    """
           action function 
    """ 
    firstClick = True
    def discoverCase(self, case_row, case_column):
        #if has click in the grid
        if (0<=case_row and case_row < self.row) and (0<=case_column and case_column < self.column ) :
            case_row = int(case_row)
            case_column = int(case_column)
            case_to_discover = self.gameboard_matrice[case_row][case_column]
                    
            case_to_discover.discover()
            case_to_discover.generateStatue()
            
            #init mines at first click
            if self.firstClick :    
                self.initMines()   
                self.firstClick = False
                
            
            #important after mine init else it will discover all the map
            if case_to_discover.getNumberOfMineAroud() == 0 :
                case_to_discover_stack , cases_pos = self.getCaseAround(case_row, case_column)
                while len(case_to_discover_stack)>0 :
                    new_case_to_discover = case_to_discover_stack.pop()
                    #print(len(case_to_discover_stack))
                    new_case_to_discover.discover()
                    new_case_to_discover.generateStatue()
                    
                    new_case_pos = cases_pos.pop()
                    
                    if new_case_to_discover.getNumberOfMineAroud() == 0 :
                        new_case_to_discover_stack, new_pos_to_add = self.getCoveredCasesAround(new_case_pos[0], new_case_pos[1])
                        case_to_discover_stack += new_case_to_discover_stack
                        cases_pos += new_pos_to_add
            #"""    
            #print(bomb_around)
            
    def getCaseAround(self,case_row,case_column):
        #          mmm
        #          mom
        #          mmm
        #stock the case 'm' in the pattern with 'o' as the case_to_discover
        case_around = []
        case_around_pos = []    
        
        row_range = range(self.row)
        column_range = range(self.column)
            
        column_indexes = [case_column-1,case_column,case_column+1]
        row_indexes = [case_row-1, case_row,case_row+1]
        for col in column_indexes :
            for row in row_indexes :
                if col in column_range and row in row_range and (col != case_column or row != case_row):
                    case_around += [self.gameboard_matrice[row][col]]
                    case_around_pos += [[row, col]]
        #print(case_around_pos)
        return case_around, case_around_pos
         
    def getCoveredCasesAround(self, case_row, case_column):
        result = []
        result_pos = []
        case_around, pos = self.getCaseAround(case_row, case_column)
        for i in range(len(case_around)):
            if not case_around[i].isDiscovered():
                result += [case_around[i]]
                result_pos += [pos[i]]
        return result, result_pos
    
    #flagging button
    def flagCase(self, event):
        row_pos = (event.x-self.x_view_pos)/SIZE_X_VECTOR
        column_pos = (event.y-self.y_view_pos)/SIZE_Y_VECTOR
        #if has click in the grid
        if (0<=row_pos and row_pos < self.row) and (0<=column_pos and column_pos < self.column ) :
            case_to_flag = self.gameboard_matrice[int(row_pos)][int(column_pos)]
            
            if case_to_flag.isFlagged():
                case_to_flag.unflag()
            else:
                case_to_flag.flag()
                
            case_to_flag.generateStatue()
            
            
    def initMines(self):
        minePlaced = 0
        while(minePlaced < self.mine_number):
            row_pos = getRandInt(0, self.row-1)
            col_pos = getRandInt(0, self.column-1)
            case_to_set = self.gameboard_matrice[row_pos][col_pos]
            if not case_to_set.hasMine():
                if case_to_set.setMine() :
                    minePlaced += 1
                    case_to_set.generateStatue()
                    cases_around_mine, cases_pos = self.getCaseAround(row_pos, col_pos)
                    for case in cases_around_mine :
                        case.addMineToNumberOfMineAround()

root = tkinter.Tk()
app = WinApp(row = 20, column = 20, mines = 50, master = root)
def _quit():
    print("app closed")
    root.destroy()
root.protocol("WM_DELETE_WINDOW", _quit)
app.mainloop()
