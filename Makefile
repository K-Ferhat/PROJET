all: one_dim_color three_dim_color exec_one_dim_color exec_three_dim_color
one_dim_color: mean_shift.c one_dim_color.c
	gcc -lm -g -o ex_one_dim_color mean_shift.c one_dim_color.c `imlib2-config --cflags --libs`

three_dim_color: mean_shift.c one_dim_color.c
	gcc -lm -g -o ex_three_dim_color mean_shift.c three_dim_color.c `imlib2-config --cflags --libs`

exec_one_dim_color:
	./ex_one_dim_color olena.jpg one_dim_color.jpg 100 > debug.txt

exec_three_dim_color:
	./ex_three_dim_color olena.jpg three_dim_color.jpg 100 > debug.txt
