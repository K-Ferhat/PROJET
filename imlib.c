#include "imlib.h"

unsigned char * read_grayscale(char *fname, int *dimx, int *dimy)
{
    Imlib_Image *image;

    image = (Imlib_Image *)imlib_load_image(fname);
    if(image)
    {
        unsigned char *buf, *data;
        int l,c;

        imlib_context_set_image( image);
        *dimx = imlib_image_get_width();
        *dimy = imlib_image_get_height();
        data  = (unsigned char *)imlib_image_get_data();
        buf = (unsigned char*) malloc(sizeof(char)**dimx**dimy);
        for(l=0;l<*dimy;l++)
	  for(c=0;c<*dimx;c++)
            {
                *buf++ = (*data + *(data+1) + *(data+2))/3;
                data += 4;
            }
        imlib_free_image();
        return buf-*dimx**dimy;
    }
    else
    {
        fprintf( stderr, "Erreur: image %s n'a pu etre ouverte.\n", fname);
        exit(33);
    }
}

void write_grayscale(char *fname, int dimx, int dimy, unsigned char *buf)
{
    Imlib_Image *image;
    unsigned char *data;
    int l, c;
    char *ext;

    if( !(ext = strchr( fname, '.')))
    {
        fprintf( stderr, "Erreur: format image non reconnu\n");
        exit(34);
    }

    data = (unsigned char *)malloc(sizeof(char)*dimx*dimy*4);
    for( l=0; l<dimy; l++)
      for( c=0; c<dimx; c++)
        {
            *data = *buf;
            *(data+1)= *buf;
            *(data+2) = *buf;
            *(data+3) = 0;
            buf ++; data += 4;
        }
    data -= dimx*dimy*4;
    image = (Imlib_Image *)imlib_create_image_using_data( dimx, dimy, (DATA32*)data);
    imlib_context_set_image( image);
    imlib_image_set_format(ext+1);
    imlib_save_image( fname);
    imlib_free_image();
    free( data);
}
