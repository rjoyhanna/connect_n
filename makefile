connectn.out: connectn.o connectnGameLogic.o
	gcc -g -Wall -Werror -o connectn.out connectn.o connectnGameLogic.o

connectn.o: connectn.c connectnGameLogic.h
	gcc -g -Wall -Werror -c -o connectn.o connectn.c

connectnGameLogic.o: connectnGameLogic.c connectnGameLogic.h
	gcc -g -Wall -Werror -c -o connectnGameLogic.o connectnGameLogic.c   

clear: 
	rm fr- *.o *.out
