Compilateur=gcc
CompFLAGS= -W -Wall -g -pedantic
LibsLoad=-lc
ObjPATH=obj/
BinPATH=bin/
EXEC=FAT

default: mkdir $(EXEC)

mkdir:
	@mkdir -p bin
	@mkdir -p obj

FAT: fat.o main.o
	$(Compilateur) $(ObjPATH)*.o $(LibsLoad) -o $(BinPATH)$@
#                                             $@ 	  Le nom de la cible		(ici "fonctions")
#                        $^   La liste des dépendances  (ici "fonctions.o main.o")

fat.o: fat.c
	$(Compilateur) -c $^ $(LibsLoad) -o $(ObjPATH)$@ $(CompFLAGS)

main.o: main.c
	$(Compilateur) -c $< $(LibsLoad) -o $(ObjPATH)$@ $(CompFLAGS)
#                     $< 	Le nom de la première dépendance	(ici pas utile car une seule dépendance)

clean:
	rm -rf $(ObjPATH)*.o 
#               suppr les fichiers objets

mrproper:
	rm -rf $(ObjPATH)*.o $(BinPATH)$(EXEC).exe
#               suppr les fichiers objets et l'executable