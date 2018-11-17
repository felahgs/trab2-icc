/**
 * @file geraMat.c
 * @brief Criação e Operação com matrizes
 */

#include <stdlib.h>
#include <stdio.h> 
#include <math.h>

#include "utils.h"
#include "geraMat.h"
/***********************
 * @brief Função que gera os coeficientes de um sistema linear k-diagonal
 * @param i coordenada da linha do elemento a ser calculado (0<=i)
 * @param j coordenada da coluna do elemento a ser calculado (j<n)
 * @param k numero de diagonais da matriz A
 ***********************/
inline double generateRandomA( unsigned int i, unsigned int j, unsigned int k )
{
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return ( (i==j)?(double)(k<<1) : 1.0 )  * (double)rand() * invRandMax;
}

/***********************
 * @brief Função que gera os termos independentes de sistema linear k-diagonal
 * @param k numero de diagonais da matriz A
 ***********************/
inline double generateRandomB( unsigned int k ) 
{
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return (double)(k<<2) * (double)rand() * invRandMax;
}

/***********************
 * @brief Função que produz uma matriz de testes
 * @param m numero de linhas da matriz 
 * @param n numero de colunas da matriz
 * 
 * Coordenadas da matriz são iniciadas na coordenada 0 e vão até n-1 (C array)
 ***********************/
 double *createTestMatrix (unsigned int m, unsigned int n) 
 {
    double *arr = (double *)malloc(m * n * sizeof(double));
 
    int i, j, count = 0;
    for (i = 0; i <  m; i++) {
      for (j = 0; j < n; j++) 
      {
         *(arr + i*n + j) = ++count;
      }
    }
      
    return arr;
 }
 
 /***********************
 * Função gera uma matriz nula
 * 
 * @param n dimensão da matriz 
 * @param k numero de diagonais da matriz A
 ***********************/
  double *generateZeroMatrix (unsigned int m, unsigned int n) 
 {
    double *arr = (double *)malloc(m * n * sizeof(double));
 
    // int i, j;
    // for (i = 0; i <  m; i++) {
    //   for (j = 0; j < n; j++) 
    //   {
    //     *(arr + i*n + j) = 0;
    //   }
    // }
    return arr;
 }
 
 /***********************
 * @brief Função que produz uma matriz esparsa  k-diagonal
 * @param n dimensão da matriz 
 * @param k numero de diagonais da matriz A
 * 
 * Produz uma matriz esparsa  k-diagonal utilizando generateRandomA
 * e popula as diagonais de acordo com o parâmetro "k" que indica o número de
 * diagonais com coeficientes diferentes de 0.
 * 
 * As coordenadas da matriz são iniciadas na coordenada 0 e vão até n-1 seguindo
 * os tamanhos padrões de arrys em C.
 * 
 * As diagonais são definidas pelo parâmetro "k" onde k é sempre ímpar, caso
 * k sejá maior que o número de diagonais máximas para a matriz de dimensão n,
 * a matriz gerada será completamente preenchida com o maior número de diagonais
 * possíveis para dada matriz, ou seja, ela será totalmente preenchida não 
 * possuindo nenhum valor 0.
 ***********************/
  double *generateBandMatrix (unsigned int n, unsigned int k) 
 {
    double *arr = (double *)malloc(n * n * sizeof(double));
    int m = (k+1)/2, i, j;
 
    for (i = 0; i <  n; i++) 
      for (j = 0; j < n; j++) 
      {
        *(arr + i*n + j) = 0;
        if( (j>=i && j<(i+m)) || (j<i && j>(i-m)) )
          *(arr + i*n + j) = generateRandomA(i,j,k);
      }
    
    return arr;
 }
 
 /***********************
 * @brief Função que gera o array de termos independentes do sistema a ser calculado
 * 
 * @param n dimensão da matriz que resulta nos termos
 * @param k numero de diagonais da matriz A
 * @return double array de termos independentes gerados
 ***********************/
 double *generateIndTerms (unsigned int n, unsigned int k)
 {
  // int i;
  int i, count = 50;
  double *arr = (double *)malloc(n * sizeof(double));
  for (i = 0; i <  n; i++) {
    *(arr + i) = generateRandomB(k);
  }
  return arr;
 }
 
  /***********************
 * @brief Cria uma copia do array passado como parametro
 * @param *arr matriz a ser copiada
 * @param m numero de linhas da matriz 
 * @param n numero de colunas da matriz
 ***********************/
 
 double *copyMatrix (double *arr, unsigned int m, unsigned int n) 
 {
    double *newArr = (double *)malloc(m * n * sizeof(double));
 
    int i, j, count = 0;
    for (i = 0; i <  m; i++) {
      for (j = 0; j < n; j++) 
      {
         *(newArr + i*n + j) = *(arr + i*n + j);
      }
    }
      
    return newArr;
 }
 
 /***********************
 * @brief Função que calcula a transposta de uma matriz devolvendo á como uma array
 * de double
 * @param m número de linhas da matriz original
 * @param n número de colunas da matriz original
 ***********************/
double *transposeMatrix(double *arr, unsigned int m, unsigned int n)
{
  double *arrT = (double *)malloc(m * n * sizeof(double));
  unsigned int i, j;
  for (i = 0; i <  m; i++) 
    for (j = 0; j < n; j++) 
      *(arrT + j*m + i) = *(arr + i*n + j);
  return arrT;
}

  /***********************
 * @brief Retorna a matriz diagonal correspondente da matriz quadrada passada
 * @param *arr matriz para se tirar a diagonal
 * @param m dimensões da matriz
 * @return a matriz diagonal de arr
 ***********************/
double *getDiagonal(double *arr, unsigned int m)
{
  double *arrD = (double *)malloc(m * m * sizeof(double));
  unsigned int i, j;
  for (i = 0; i <  m; i++) 
    for (j = 0; j < m; j++) 
    {
      if(i == j) 
        *(arrD + j*m + i) = *(arr + j*m + i);
      else 
        *(arrD + j*m + i) = 0;
    }
  return arrD;
}

  /***********************
 * @brief Retorna a matriz inversa de uma matriz diagonal. A matriz parametro deve
 * ser uma matriz diagonal, caso contrario a saída não ser correta
 * 
 * @param *arr matriz diagonal para calcular sua inversa
 * @param m dimensões da matriz


 * @return a matriz diagonal de arr
 ***********************/
double *invDiagonal(double *arr, unsigned int m)
{
  double *arrI = (double *)malloc(m * m * sizeof(double));
  unsigned int i, j;
  for (i = 0; i <  m; i++) 
    for (j = 0; j < m; j++) 
      if(i == j) 
        *(arrI + j*m + i) = (1 / *(arr + j*m + i));
      else 
        *(arrI + j*m + i) = 0;
  return arrI;
}

  /***********************
 * @brief Soma tudas matrizes de mesmas dimensões
 * @param *arr1 primeira matriz da soma
 * @param *arr2 segunda matriz da soma
 * @param m numero de linhas das matrizes
 * @param n numero de colunas das matrizes

 * @return a matriz resultante da soma de ambas as entradas
 ***********************/
 
 double *sumMatrix (double *arr1, double *arr2, unsigned int m, unsigned int n)
 {
    double *newArr = (double *)malloc(m * n * sizeof(double));
 
    int i, j;
    for (i = 0; i <  m; i++) {
      for (j = 0; j < n; j++) 
      {
         *(newArr + i*n + j) = *(arr1 + i*n + j) + *(arr2 + i*n + j);
      }
    }
      
    return newArr;
 }
 
   /***********************
 * @brief Subtrai tudas matrizes de mesmas dimensões
 * @param *arr1 primeira matriz da soma
 * @param *arr2 segunda matriz da soma
 * @param m numero de linhas das matrizes
 * @param n numero de colunas das matrizes

 * @return a matriz resultante da soma de ambas as entradas
 ***********************/
 
 double *subtractMatrix (double *arr1, double *arr2, unsigned int m, unsigned int n)
 {
    double *newArr = (double *)malloc(m * n * sizeof(double));
 
    int i, j;
    for (i = 0; i <  m; i++) {
      for (j = 0; j < n; j++) 
      {
         *(newArr + i*n + j) = *(arr1 + i*n + j) - *(arr2 + i*n + j);
      }
    }
      
    return newArr;
 }

 /***********************
 * @brief Calcula o produto de duas matrizes e retorna o resultado como uma nova
 * @param *arr1 ponteiro para a primeira matriz
 * @param m1 número de linhas da matriz primeira matriz
 * @param n1 número de colunas da matriz primeira matriz
 * @param *arr1 número de linhas da matriz original
 * @param m2 número de linhas da segunda matriz
 * @param n2 número de colunas segunda matriz
 * 
 * @return Devolve um ponteiro com o resultado da multiplicação arr1 X arr2
 ***********************/
double *multiplyMatrix(double *arr1, unsigned int m1, unsigned int n1,
          double *arr2, unsigned int m2, unsigned int n2) 
{
  double sum, *arrR = (double *)malloc(m1 * n2 * sizeof(double));
  unsigned int i, j, k;
  for ( i = 0; i < m1; i++) 
  {
    for (j = 0; j < n2; j++) 
    {
      sum = 0;
      for (k = 0; k < m2; k++)
      {
        sum = sum + ( *(arr1 + i*n1 + k) * *(arr2 + k*n2 + j) );
      }
      *(arrR + i*n2 + j) = sum;
    }
  }
    return arrR;
}


   /***********************
 * @brief Retorna maior elemento do array
 * @param *arr 
 * @param m dimensões do array

 * @return max maior elemento do array
 ***********************/
 
 double maxN (double *arr, unsigned int m, unsigned int n)
 {
    int i;
    float max = 0;
    for (i = 0; i <  m*n; i++) 
    {
        if (max < *(arr + i));
         max = *(arr + i);
    }
    return max;
 }
 
    /***********************
 * @brief Retorna a norma euclidiana da matriz
 * @param *A matriz principal
 * @param *b vetor de termos independentes
 * @param *x vetor de resultados 
 * @param n dnimensão da matriz 
 * @param variável para o calculo do tempo da função

 ***********************/
 
 double calculateNorm (double *A, double *b, double *x, int n, double *nTime)
 {
    *nTime = timestamp();
    double *aux, *aux1, norm;
    aux = multiplyMatrix(A, n, n, x, n, n);
    aux1 = subtractMatrix(b, aux, n, 1);
    
    norm = fabs(maxN(aux1, n, 1));
    
    *nTime = timestamp() - *nTime;
    free (aux); free (aux1);
    
    return norm;
    
 }
 
  /**
 *  Funcao prnMat:  Imprime o conteudo de uma matriz em stdout
 *  @param mat matriz
 *  @param n ordem da matriz quadrada
 *
 */

void prnMat (double *mat, int n)
{
  int i, j;
  for (i=0; i < n; ++i) {
    for (j=0; j < n; ++j)
      printf(DBL_FIELD, MAT(mat,n,i,j));
    printf("\n");
  }
  printf(SEP_RES);
}


void prnArr (double *vet, int n)
{
  for (int i=0; i < n; ++i)
    printf(DBL_FIELD, vet[i]);
  printf(SEP_RES);
}


