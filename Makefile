all:main.c
	gcc -o main main.c -lhiredis -lpthread -L /usr/local/lib
