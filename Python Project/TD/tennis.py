score_joueur1 = 0
score_joueur2 = 0
joueur1 = "joueur1"
joueur2 = "joueur2"
def win_game(winner,score1, score2) :
        print("C'est le",winner,"qui a gagné avec un score de ", score1,"contre", score2)
        return winner

nombre_partie = int(input("Veuillez entrer le nombre de partie qui s'est effectué : " ))
mark_point = []
for i in range(nombre_partie) :
        mark_point.append(int(input("Veuillez entrer successivement qui du joueur 1 ou 2 a gagné le point au cours de ces parties :")))
        print(mark_point)
def score2(mark_point,score_joueur1,  score_joueur2,nombre_partie,joueur1, joueur2):

    for k in mark_point:
                if k == 2:
                    score_joueur2 +=1
                    print("le score du joueur 2 est",score_joueur2)
                elif k == 1:
                    score_joueur1 += 1
                    print("le score du joueur 1 est",score_joueur1)

    difference1 = score_joueur2 - score_joueur1
    difference2 = score_joueur1 - score_joueur2
    print(difference1)
    print(difference2)
    while  (difference1 < 2) and (difference2 < 2)   :
        nombre_partie += 1
        for i in range(nombre_partie) :
            mark_point.append(int(input("Veuillez entrer successivement qui du joueur 1 ou 2 a gagné le point au cours des parties suivantes :")))
            print(mark_point)
            for k in mark_point:
                if k == 2:
                    score_joueur2 +=1
                    print("le score du joueur 2 est",score_joueur2)
                elif k == 1:
                    score_joueur1 += 1
                    print("le score du joueur 1 est",score_joueur1)
    if score_joueur2 > score_joueur1:
         win_game(joueur2,score_joueur2, score_joueur1)

    elif score_joueur2 < score_joueur1:

          win_game(joueur1, score_joueur1, score_joueur2)
    else:
        score2(mark_point,score_joueur1,  score_joueur2,nombre_partie,joueur1, joueur2)



def set_tennis() :
    set_gagnant = int(input("Veuillez entrer en combien de set gagnant le match est joué"))
    set_joueur1 = 0
    set_joueur2 = 0
    jeu_joueur1 = 0
    jeu_joueur2 = 0
    while set_joueur2 < set_gagnant and set_joueur1 < set_gagnant :
        n = 6
        
        for i in range (n):
            while jeu_joueur2 - joueur1 < 2 and jeu_joueur1 - jeu_joueur2 < 2 :
                score2(mark_point,score_joueur1,  score_joueur2,nombre_partie)
                if winner == joueur1 :
                    jeu_joueur1 += 1
                else :
                    jeu_joueur2 +=1
                if jeu_joueur1 == 6 and jeu_joueur2 == 6 :
                    tie_break()
                    break
        if jeu_joueur2 > jeu_joueur1:
             set_joueur2 += 1
    
        elif jeu_joueur2 < jeu_joueur1:
             set_joueur1 += 1 
        else:
            set_tennis()
    if set_joueur2 == set_gagnant:
         print("C'est le  joueur2 qui a gagné ")
    elif set_joueur1 == set_gagnant:
         print("C'est le  joueur1 qui a gagné ")
        
def tie_break (set_joueur1,set_joueur2):
    score_joueur_1 = 0
    score_joueur_2 = 0
    point_marque = []
    partie_joue= int(input("Veuillez entrer le nombre de partie qui s'est effectué" ))
    for g in range(partie_joue):
        point_marque.append(int(input("Veuillez entrer successivement qui du joueur 1 ou 2 a gagné le point au cours de ces parties :")))
        print(point_marque)
    for m in point_marque:
        if m == 2:
            score_joueur_2 +=1
            print("le score du joueur 2 est",score_joueur_2)
        elif m == 1:
            score_joueur_1 += 1
            print("le score du joueur 1 est",score_joueur_1)
    difference_1 = score_joueur_2 - score_joueur_1
    difference_2 = score_joueur_1 - score_joueur_2
    if (score_joueur_1 == 7 ) and (difference_1 >= 2):
        set_joueur1 +=1
    elif (score_joueur_2 == 7 ) and (difference_2 >= 2):
        set_joueur2 +=1
    else:
        while  (difference_1 < 2) and (difference_2 < 2)   :
            partie_joue += 1
            for i in range(partie_joue) :
                point_marque.append(int(input("Veuillez entrer successivement qui du joueur 1 ou 2 a gagné le point au cours des parties suivantes :")))
                print(point_marque)
                for k in point_marque:
                    if k == 2:
                        score_joueur_2 +=1
                        print("le score du joueur 2 est",score_joueur_2)
                    elif k == 1:
                        score_joueur_1 += 1
                        print("le score du joueur 1 est",score_joueur_1)
        
        
    print(difference_1)
    print(difference_2)
    while  (difference_1 < 2) and (difference_2 < 2)   :
        partie_joue += 1
        for i in range(partie_joue) :
            point_marque.append(int(input("Veuillez entrer successivement qui du joueur 1 ou 2 a gagné le point au cours des parties suivantes :")))
            print(point_marque)
            for k in point_marque:
                if k == 2:
                    score_joueur_2 +=1
                    print("le score du joueur 2 est",score_joueur_2)
                elif k == 1:
                    score_joueur_1 += 1
                    print("le score du joueur 1 est",score_joueur_1)

        if score_joueur_2 > score_joueur_1:
            set_joueur2 +=1
            
        elif score_joueur2 < score_joueur1:
            set_joueur1 +=1
set_tennis()
          
   
                
            
