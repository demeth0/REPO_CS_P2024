# Minesewer
<p style="border: 3px solid black;">pas encore finis :  
	<ul><li>condition d'arret (gagner perdre)</li>  
	<li>interface graphique (bouton, selection / changement parametre)</li></ul>  </p>

<p>J'ai pas eu le temps de commenter je le fait des que je peut pour les edits</p>
</br> 
<p>customisation possible avec les variables en début de code (en majuscule)  </p>
 <table>
 	<tr> 
 		<th> 
 			Nom
 		</th>
 		<th> 
 			Default value
 		</th>
 		<th> 
 			comment
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			FRAME_WIDTH
 		</th>
 		<th> 
 			 700 px
 		</th>
 		<th> 
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			FRAME_HEIGHT
 		</th>
 		<th> 
 		 	500 px
 		</th>
 		<th> 
 		</th>
 	</tr>
 	<tr> 
 		<th> 
			BOARD_REFRESH_RATE
 		</th>
 		<th> 
 			int(1000/60)
 		</th>
 		<th> 
 			the value is in ms
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			BOARD_WIDTH
 		</th>
 		<th> 
 		 	500 px
 		</th>
 		<th> 
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			BOARD_HEIGHT
 		</th>
 		<th> 
 			500 px
 		</th>
 		<th> 
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			BOARD_BACKGROUND
 		</th>
 		<th> 
 			"black"
 		</th>
 		<th> 
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			CASE_WIDTH
 		</th>
 		<th> 
 			1
 		</th>
 		<th> 
 			CASE_HEIGHT == CASE_WIDTH  1 represent the relation with the vector X and Y (1*SIZE_X_VECTOR, 1*SIZE_X_VECTOR)
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			SIZE_X_VECTOR
 		</th>
 		<th> 
 			30 px
 		</th>
 		<th> 
 			if you want to change the scale of the canvas you also need to resize the textures
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			SIZE_Y_VECTOR
 		</th>
 		<th> 
 			30 px
 		</th>
 		<th> 
 			if you want to change the scale of the canvas you also need to resize the textures
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			RES_MINE_CASE
 		</th>
 		<th> 
 			"mine_case_x30.gif"
 		</th>
 		<th> 
 			only the file name, will be concatenatedwith the EXTERNAL_RES_FILE_PATH
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			RES_COVERED_CASE
 		</th>
 		<th> 
 			"covered_case_x30.gif"
 		</th>
 		<th> 
 			only the file name, will be concatenatedwith the EXTERNAL_RES_FILE_PATH
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			RES_DISCOVERED_CASE
 		</th>
 		<th> 
 			"discovered_case_x30.gif"
 		</th>
 		<th> 
 			only the file name, will be concatenatedwith the EXTERNAL_RES_FILE_PATH. Cette variable n'est pas utilisée deja comprise dans RES_DISCOVERED_CASE_TAGGED
 		</th>
 	</tr>
 	<tr>
 		<th> 
 			RES_FLAGGED_CASE
 		</th>
 		<th> 
 			"flagged_case_x30.gif"
 		</th>
 		<th> 
 			only the file name, will be concatenatedwith the EXTERNAL_RES_FILE_PATH
 		</th>
 	</tr>
 	<tr> 
 		<th> 
 			RES_DISCOVERED_CASE_TAGGED
 		</th>
 		<th> 
 			["discovered_case_x30.gif","discovered_case_1_x30.gif",  "discovered_case_2_x30.gif","discovered_case_3_x30.gif",   "discovered_case_4_x30.gif","discovered_case_5_x30.gif",  "discovered_case_6_x30.gif","discovered_case_7_x30.gif",  "discovered_case_8_x30.gif"]
 		</th>
 		<th> 
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
 	


  
