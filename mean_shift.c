#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imlib.h"

double kernel(double x){
	if(x<=1)
		return 1.5*(1.0-x*x);
	return 0.0;
}

double derivee_kernel(double x){
	if(x <= 1)
		return -3.0*x;
	return 0.0;
}


void build_histogram(unsigned char *original_dot_set, unsigned int cardinal, unsigned int *hist){

	unsigned int i;

	/*Initialisation du tableau a 0 pour les ++ d'apres*/
	for(i = 0; i < 256; i++){
		hist[i] = 0;
	}

	/*pour chaque valeur de pixel on ajoute 1 dans la case correspondante*/
	for(i = 0; i < cardinal; i++){
		hist[original_dot_set[i]]++;
	}

}

/* val c'est la valeur du pixel qu'on veut faire converger, h c'est la bande passante*/
void mean_shift(unsigned char *original_dot_set, unsigned int *shifted_hist,  unsigned int cardinal, unsigned char h, unsigned char val, unsigned int *hist){

	printf("NEW PIXEL\n");
	double scale_factor = 0.0;/*den*/
	double numerator = 0.0;
	int i;
	int error = 1;
	shifted_hist[val] = val;

	while(error > 0){
		printf("-");
		/*i represente xi*/
		for(i = 1; i <= 255; i++){
			//numerator += hist[i] * i * (-1.0)  * derivee_kernel(((val-i)/h)*(val-i)/h);
			//scale_factor += hist[i] * (-1.0) * derivee_kernel(((val-i)/h)*(val-i)/h);
			numerator += hist[i] * i * kernel(((val-i)/h)*(val-i)/h);
			scale_factor += hist[i] * kernel(((val-i)/h)*(val-i)/h); 
		}
    
		error = shifted_hist[val];

		shifted_hist[val] = (unsigned int)(numerator / scale_factor);

		error -= shifted_hist[val];
		if(error < 0) error = -error;	
	}
	printf("\n");
}


void compute_mean_shift(unsigned char *original_dot_set, unsigned char *shifted_dot_set, unsigned int cardinal, unsigned char h){
	unsigned int i;
	unsigned int *hist = malloc(sizeof(unsigned int) * 256);
	unsigned int *shifted_hist = malloc(sizeof(unsigned int) * 256);

	/*construction de l'histogramme*/
	build_histogram(original_dot_set, cardinal, hist);

	/*application du mean shift sur chaque valeur de l'histogramme*/
	for(i = 0; i < 256; i++){
		mean_shift(original_dot_set, shifted_hist, cardinal, h, i, hist );
	}

	printf("VALEUR DE L'HISTOGRAMME\n");
	for(i = 0; i < 256; i++){
		printf("%d ", hist[i]);
	}
	putchar('\n');
  
	printf("VALEUR DE SHIFTED HIST\n");
	for(i = 0; i < 256; i++){
		printf("%d ", shifted_hist[i]);
	}
	putchar('\n');
  
	for(i = 0; i < cardinal; i++){
		shifted_dot_set[i] = shifted_hist[original_dot_set[i]];
	}
	build_histogram(shifted_dot_set, cardinal, hist);
    printf("VALEUR DE L'HISTOGRAMME\n");
	for(i = 0; i < 256; i++){
		printf("%d ", hist[i]);
	}
	putchar('\n');
  
}
