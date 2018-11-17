/**
 * @file gradients.h
 * @brief Funções para calculo de gradientes conjugados
 */
 
#ifndef __GRADIENTS_H__
#define __GRADIENTS_H__
 
 double *conjugateGradients(double *A, double *b, unsigned int n, 
      unsigned int maxIt, double eps, FILE *fp);
double *preconditioningCg(double *A, double *B, double * M, unsigned int n, 
      unsigned int maxIt, double eps, FILE *fp);
      
#endif //__GRADIENTS_H__