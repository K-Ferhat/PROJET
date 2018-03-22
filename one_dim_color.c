#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Imlib2.h>
#include <string.h>
#include "imlib.h"
#include "mean_shift.h"


double radially_symetric_der(double x){
	if(x <= 1)
		return -3.0*x;
	return 0.0;
}

double gaussian_der(double x){
	if(x <= 1)
		return -3.0*x;
	return 0.0;
}

int main(int argc, char **argv){
	char *arg;
	char *param;
	
	double h = 20.0;
	char *inName = NULL, *outName = NULL;

	/* To change the kernel function easily */
	double (*kernel_function)(double) = radially_symetric_der;

	/* Parse command line arguments */
	if(argc > 1){
		for(int i = 1; i < argc; i++) {
			arg = argv[i];
			param = NULL;

			if(arg[0] == '-' && i+1 < argc) param = argv[i+1];

			if((strcmp("-input", arg) == 0 || strcmp("-in", arg) == 0) && param != NULL) {
				i++;
				inName = param;
			}
			else if((strcmp("-output", arg) == 0 || strcmp("-out", arg) == 0) && param != NULL) {
				i++;
				outName = param;
			}
			else if((strcmp("-bandwidth", arg) == 0 || strcmp("-h", arg) == 0) && param != NULL) {
				i++;
				h = atof(param);
			}
			else if((strcmp("-kernel", arg) == 0 || strcmp("-k", arg) == 0) && param != NULL) {
				i++;
				if(strcmp("radially_symmetric", param) == 0)  kernel_function = radially_symetric_der ;
				if(strcmp("gaussian", param) == 0) kernel_function = gaussian_der;
			}
		}

	}

	else{
		fprintf(stderr, "Run default execution : h=20, inName=\"olena.jpg\", outName=\"one_dim_color.jpg\", kernel=radially_symetric\n\nUsage :\n\t-input / -in : input file\n\t-output / -out : output file\n\t-bandwidth / -h : set h parameter\n");
	}


	
	unsigned char *buf_in, *buf_out;
	int dimx, dimy; /* nombre de colonnes, de lignes de l'image */
	
	/* lecture image */
	if(inName == NULL) buf_in = read_grayscale("olena.jpg", &dimx, &dimy);
	else buf_in = read_grayscale(inName, &dimx, &dimy);

	write_grayscale("original_dot_set.jpg", dimx, dimy, buf_in);

	/* traitement sur l'image */
	buf_out = (unsigned char *)malloc(sizeof(unsigned char)*dimx*dimy);

	compute_mean_shift(buf_in, buf_out, dimx * dimy, h, kernel_function);

	/* ecriture image */
	if (outName == NULL) write_grayscale("one_dim_color.jpg", dimx, dimy, buf_out);
	else write_grayscale(outName, dimx, dimy, buf_out);
			
	free(buf_in);
	free(buf_out);
    
	return 0;
}
