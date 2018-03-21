all: one_dim_color exec_one_dim_color

one_dim_color: mean_shift.c one_dim_color.c
	gcc -lm -g -Wall -o ex_one_dim_color mean_shift.c one_dim_color.c `imlib2-config --cflags --libs`

exec_one_dim_color:
	./ex_one_dim_color olena.jpg one_dim_color.jpg 40 > debug.txt

clean:
	rm ex_one_dim_color original_dot_set.jpg one_dim_color.jpg
