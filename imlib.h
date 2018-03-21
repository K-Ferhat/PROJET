/*
 * D.Béréziat (c) 2011 pour UPMC.
 *
 * Routine de chargement/traitement/sauvegarde d'image simplifiée
 * avec imlib2: un grand nombre de formats sont gérés.
 * Installation sur Ubuntu/Debian: copiez-coller la ligne suivante dans le terminal:
 *  sudo apt-get install libimlib2-dev
 * Installation pour Mac: copiez-coller les deux lignes suivantes dans le terminal:
 *  curl /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
 *  brew install imlib2
 * Compilation:
 *  gcc imlib-exemple.c -o imlib-exemple `imlib2-config --cflags --libs`
 * ou encore :
 *  make
 */

#include <Imlib2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned char * read_grayscale(char *fname, int *dimx, int *dimy);

void write_grayscale(char *fname, int dimx, int dimy, unsigned char *buf);
