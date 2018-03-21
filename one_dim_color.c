#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Imlib2.h>
#include <string.h>
#include "imlib.h"
#include "mean_shift.h"


int main(int argc, char **argv){
	char *inName, *outName;
    double h;
    if(argc > 3)
		{
			unsigned char *buf_in, *buf_out;
			int dimx, dimy; /* nombre de colonnes, de lignes de l'image */
			
			/* parametres de la commande */
			inName=argv[1];
			outName=argv[2];
			h = atof(argv[3]);
			
			/* lecture image */
			buf_in = read_grayscale(inName, &dimx, &dimy);
			write_grayscale("original_dot_set.jpg", dimx, dimy, buf_in);
			/* traitement sur l'image */
			buf_out = (unsigned char *)malloc(sizeof(unsigned char)*dimx*dimy);

			compute_mean_shift(buf_in, buf_out, dimx* dimy,h);

			/* ecriture image */
			write_grayscale(outName, dimx, dimy, buf_out);
			
			free(buf_in);
			free(buf_out);
		}
    else{
        printf("Usage: %s image-in image-out seuil\n", *argv);
	}
	
	return 0;
}
