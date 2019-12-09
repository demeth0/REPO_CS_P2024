# Minesewer
pas encore finis :  
	condition d'arret (gagner perdre)  
	interface graphique (bouton, selection / changement parametre)  
  
customisation possible avec les variables en début de code (en majuscule)  
 <table>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			Nom
 		</th>
 		<th> <!-->valeur par def<-->
 			Default value
 		</th>
 		<th> <!-->commentaire<-->
 			comment
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			FRAME_WIDTH
 		</th>
 		<th> <!-->valeur par def<-->
 			 700 px
 		</th>
 		<th> <!-->commentaire<-->
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			FRAME_HEIGHT
 		</th>
 		<th> <!-->valeur par def<-->
 		 	500 px
 		</th>
 		<th> <!-->commentaire<-->
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
			BOARD_REFRESH_RATE
 		</th>
 		<th> <!-->valeur par def<-->
 			int(1000/60)
 		</th>
 		<th> <!-->commentaire<-->
 			the value is in ms
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			BOARD_WIDTH
 		</th>
 		<th> <!-->valeur par def<-->
 		 	500 px
 		</th>
 		<th> <!-->commentaire<-->
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			BOARD_HEIGHT
 		</th>
 		<th> <!-->valeur par def<-->
 			500 px
 		</th>
 		<th> <!-->commentaire<-->
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			BOARD_BACKGROUND
 		</th>
 		<th> <!-->valeur par def<-->
 			"black"
 		</th>
 		<th> <!-->commentaire<-->
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			CASE_WIDTH
 		</th>
 		<th> <!-->valeur par def<-->
 			1
 		</th>
 		<th> <!-->commentaire<-->
 			CASE_HEIGHT == CASE_WIDTH  1 represent the relation with the vector X and Y (1*SIZE_X_VECTOR, 1*SIZE_X_VECTOR)
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			SIZE_X_VECTOR
 		</th>
 		<th> <!-->valeur par def<-->
 			30 px
 		</th>
 		<th> <!-->commentaire<-->
 			if you want to change the scale of the canvas you also need to resize the textures
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			SIZE_Y_VECTOR
 		</th>
 		<th> <!-->valeur par def<-->
 			30 px
 		</th>
 		<th> <!-->commentaire<-->
 			if you want to change the scale of the canvas you also need to resize the textures
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			RES_MINE_CASE
 		</th>
 		<th> <!-->valeur par def<-->
 			"mine_case_x30.gif"
 		</th>
 		<th> <!-->commentaire<-->
 			only the file name, will be concatenatedwith the EXTERNAL_RES_FILE_PATH
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			RES_COVERED_CASE
 		</th>
 		<th> <!-->valeur par def<-->
 			"covered_case_x30.gif"
 		</th>
 		<th> <!-->commentaire<-->
 			only the file name, will be concatenatedwith the EXTERNAL_RES_FILE_PATH
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			RES_DISCOVERED_CASE
 		</th>
 		<th> <!-->valeur par def<-->
 			"discovered_case_x30.gif"
 		</th>
 		<th> <!-->commentaire<-->
 			only the file name, will be concatenatedwith the EXTERNAL_RES_FILE_PATH
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			RES_FLAGGED_CASE
 		</th>
 		<th> <!-->valeur par def<-->
 			"flagged_case_x30.gif"
 		</th>
 		<th> <!-->commentaire<-->
 			only the file name, will be concatenatedwith the EXTERNAL_RES_FILE_PATH
 		</th>
 	</tr>
 	<tr> <!-->*12<-->
 		<th> <!-->nom<-->
 			RES_DISCOVERED_CASE_TAGGED
 		</th>
 		<th> <!-->valeur par def<-->
 			["discovered_case_x30.gif","discovered_case_1_x30.gif","discovered_case_2_x30.gif","discovered_case_3_x30.gif","discovered_case_4_x30.gif","discovered_case_5_x30.gif","discovered_case_6_x30.gif","discovered_case_7_x30.gif","discovered_case_8_x30.gif"]
 		</th>
 		<th> <!-->commentaire<-->
 			only the file name, will be concatenatedwith the EXTERNAL_RES_FILE_PATH
 		</th>
 	</tr>
 	<tr>
 		<th>
 			EXTERNAL_RES_FILE_PATH
 		</th>
 		<th>
 			"ressources\\"
 		</th>
 		<th>
 			absolute name or relative name to the file minesewer.py
 		</th>
 	</tr>

</table>
 	

EXTERNAL_RES_FILE_PATH = "ressources\\"


J'ai pas eu le temps de commenter je le fait des que je peut pour les edits.  