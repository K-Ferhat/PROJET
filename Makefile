all: one_dim_color exec_one_dim_color

one_dim_color: mean_shift.c one_dim_color.c imlib.c imlib.h
	gcc -lm -g -Wall -o ex_one_dim_color mean_shift.c one_dim_color.c imlib.c `imlib2-config --cflags --libs`

exec_one_dim_color:
	./ex_one_dim_color -h 40 -input olena.jpg -output one_dim_color.jpg > debug.txt

plot:
	gnuplot hist/config.gnuplot

clean:
	rm debug.txt ex_one_dim_color original_dot_set.jpg one_dim_color.jpg hist/*.jpg hist/*.data
