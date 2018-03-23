#ifndef _MEAN_SHIFT_H
#define _MEAN_SHIFT_H

void compute_mean_shift(unsigned char *original_dot_set, unsigned char *shifted_dot_set, unsigned int cardinal, double h, double (*kernel_function)(double x));

#endif
