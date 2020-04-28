myshell:myshell.o utility.o
	gcc -o $@ $^
myshell.o:myshell.c
	gcc -c $<
utility.o:utility.c
	gcc -c $<