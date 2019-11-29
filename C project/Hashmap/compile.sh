#fonction d'execution pour l'option -e
execute_project(){
	echo "running program"
	./bin/Main
	echo
}

#fonction de mise a jour de git pour l'option -g
update_git(){
	#fait les changement au niveau local
	git commit -a -m "update on hashmap project"
	#fait les changement au niveau de la brache stocker serveur
	git push
}

#begin : detection des commandes
do_git=0
do_execute=0
while getopts "eg" opt
do
    case $opt in
    (e) do_execute=1 ;;
    (g) do_git=1 ;;
    (*) printf "Illegal option '-%s'\n" "$opt" && exit 1 ;;
    esac
done
#end : detection des commandes

#begin : execution des commandes

echo "start compiling"

#compile le projet dans src (main file) et genere le exe dans ./bin
gcc -o bin/Main src/Main.c 2>error.txt
echo "compilation finished"
cat error.txt
echo "--------------------------------------------------------------------------------"
(( do_execute )) && execute_project;
echo "--------------------------------------------------------------------------------"
(( do_git )) && update_git;
echo "--------------------------------------------------------------------------------"

#end : execution des commandes