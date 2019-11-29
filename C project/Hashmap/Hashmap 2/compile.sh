
echo "start compiling"
gcc -o bin/Main src/Main.c 2>error.txt

execute_project(){
	echo "running program:"
	echo "--------------------------------------------------------------------------------"
	./bin/Main
	echo
	echo "--------------------------------------------------------------------------------"
}

update_git(){
	git commit -a -m "update on hashmap project"
	git push
}
#if [ "$1" == "-e" ] ; then
#	execute_project();
#fi

do_all=1
do_git=0
do_execute=0
while getopts "eg" opt
do
    case $opt in
    (e) do_all=0 ; do_exxecute=1 ;;
    (g) do_all=0 ; do_git=1 ;;
    (*) printf "Illegal option '-%s'\n" "$opt" && exit 1 ;;
    esac
done

(( do_all || do_execute )) && execute_project;

(( do_all || do_git )) && update_git;

echo "compilation finished"