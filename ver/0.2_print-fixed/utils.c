/**
 * @file utils.c
 * @brief Calculo de tempo e impressão de matrizes
 */

#include "utils.h"
#include <stdio.h>

/***********************
 * Retorna tempo em milisegundos
 ***********************/
double timestamp(void)
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

/***********************
 * Função que imprime uma matriz quadrada de uma forma facil de ler
 * *arr: ponteiro da matriz
 * m, n: dimensões da matriz
 ***********************/
void printMat(double *arr, unsigned int m, unsigned int n, FILE *fp)
{
  unsigned int i, j;
  for (i = 0; i <  m; i++) 
  {
    for (j = 0; j < n; j++) 
    {
      fprintf(fp, "%.15g ", *(arr + i*n + j));
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");
}

void printArray(double *arr, unsigned int m, unsigned int n)
{
  for (int i = 0; i < m*n; i++)
  {
    printf("%6.2f ", *(arr + i));
  }
  printf("\n");
}

void printOutput(double r, double timePC, double timeNorm, int it,
                  double itTotal, int n, double *Rx, FILE *fp) 
{
    fprintf(fp, "# fgs12 Felipe Garcia de Souza\n");
    fprintf(fp, "# \n");
    for(int i=1; i<it;i++) {
      fprintf(fp, "# iter %d: %5.15g\n",  i, Rx[i]);
    }
    fprintf(fp, "# \n");
    fprintf(fp, "# Residuo: %.15g \n", r);
    fprintf(fp, "# Tempo PC: %.15g sec \n", (timePC / 1000));
    fprintf(fp, "# Tempo iter: %.15g sec \n", (itTotal/it) / 1000);
    fprintf(fp, "# Tempo residuo: %.15g sec \n", timeNorm/1000);
    fprintf(fp, "# \n");
    fprintf(fp,"%d\n", n);
  
}