all: compile open

compile: nouveau.c main.c
	gcc -lm -g nouveau.c main.c `imlib2-config --cflags --libs`

open:
	./a.out olena.jpg test1.jpg 100 > debug.txt
