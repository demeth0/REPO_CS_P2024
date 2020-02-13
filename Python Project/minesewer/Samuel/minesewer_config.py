# -*- coding: utf-8 -*-
"""
Created on Fri Dec 13 21:36:14 2019

@author: Samuel Dechambre
"""

BOARD_MENU_WIDTH = 200

#en ms
BOARD_REFRESH_RATE = int(1000/30)
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

#if you want to use <Button-1> as the discover key set '<ButtonRelease-1>' instead elsewhere it will conflict 
#with the drag and drop function
KEY_DISCOVER = 'a'
KEY_FLAG = 'z'