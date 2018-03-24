all: one_dim_color

one_dim_color: mean_shift.c one_dim_color.c imlib.c imlib.h
	gcc -lm -g -Wall -o ex_one_dim_color mean_shift.c one_dim_color.c imlib.c `imlib2-config --cflags --libs`

olena:
	./ex_one_dim_color -h 20 -input olena.jpg -output olena_shift.jpg

chat:
	./ex_one_dim_color -h 20 -input chat.jpg -output chat_shift.jpg

plot:
	gnuplot hist/config.gnuplot

clean:
	rm ex_one_dim_color chat_shift.jpg olena_shift.jpg hist/*.jpg hist/*.data
