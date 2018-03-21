#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imlib.h"

static double derivee_kernel(double x){
	if(x <= 1)
		return -3.0*x;
	return 0.0;
}


static void build_histogram(unsigned char *original_dot_set, unsigned int cardinal, unsigned int *hist){
	unsigned int i;

	for(i = 0; i < 256; i++){
		hist[i] = 0;
	}

	/* Dans la i eme case du tableau, on indique le nombre de pixels a i */
	for(i = 0; i < cardinal; i++){
		hist[original_dot_set[i]]++;
	}
}


static void mean_shift(unsigned char *original_dot_set, double *shifted_hist,  unsigned int cardinal, double h, unsigned int val, unsigned int *hist){

	double scale_factor = 0.0;
	double numerator = 0.0;
	unsigned int i;
	double error = 1.0;
	unsigned int step = 0;
	double kernel_argument;
	shifted_hist[val] = (double)val;


	while(error > 0.001){
		step ++;
		
		for(i = 0; i <= 255; i++){
			kernel_argument = ((shifted_hist[val]-(double)i)*(shifted_hist[val]-(double)i))/(h*h);
			
			numerator -= (double)hist[i] * (double)i * derivee_kernel(kernel_argument);
			scale_factor -= (double)hist[i] * derivee_kernel(kernel_argument);
		}
    
		error = shifted_hist[val]; /* old value */

		shifted_hist[val] = numerator / scale_factor;

		error -= shifted_hist[val]; /* old value - new value */
		if(error < 0) error = -error;
	}
	printf("The value [%d] needed %d steps to converge to %.3lf\n", val, step, shifted_hist[val]);
}


void compute_mean_shift(unsigned char *original_dot_set, unsigned char *shifted_dot_set, unsigned int cardinal, double h){
	unsigned int i;
	unsigned int *hist = malloc(sizeof(unsigned int) * 256);
	double *shifted_hist = malloc(sizeof(double) * 256);

	build_histogram(original_dot_set, cardinal, hist);

	/*Application du mean shift sur chaque valeur de l'histogramme*/
	for(i = 0; i < 256; i++){
		mean_shift(original_dot_set, shifted_hist, cardinal, h, i, hist);
	}

	/* Print input histogramme */
	puts("\n\nInput histogramme");
	for(i = 0; i < 256; i++){
		printf("%d ", hist[i]);
	}

	/* Build the final set */
	for(i = 0; i < cardinal; i++){
		shifted_dot_set[i] = (unsigned int)shifted_hist[original_dot_set[i]];
	}

	/* Print output histogramme */
	build_histogram(shifted_dot_set, cardinal, hist);
    printf("\n\nOutput histogramme\n");
	for(i = 0; i < 256; i++){
		printf("%d ", hist[i]);
	}
	putchar('\n');
}
