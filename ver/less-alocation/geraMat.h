/**
 * @file geraMat.h
 * @brief Criação e Operação com matrizes
 */
#define DBL_FIELD "%9.2lg"
// #define DBL_FIELD "%12.7lg"
#define SEP_RES "\n\n"
#define MAT(m,cols,i,j)   m[(i)*(cols)+(j)] 
// m D= matriz; cols = numero de colunas;  ixj = posição na matriz

#ifndef __GERAMAT_H__
#define __GERAMAT_H__

//Geradores de coeficientes
double generateRandomA( unsigned int i, unsigned int j, unsigned int k );
double generateRandomB( unsigned int k );

//Impressão de Matrizes
void prnMat (double *mat, int n);
void prnArr (double *vet, int n);

//Geradores de Matrizes
double *createTestMatrix (unsigned int m, unsigned int n);
double *newMatrix(unsigned int m, unsigned int n);
double *generateBandMatrix (unsigned int k, unsigned int n);
double *generateIndTerms (unsigned int n, unsigned int k);

//Operações Com Matrizes
void copyMatrix (double *A, unsigned int m, unsigned int n, double *B);
double *sumMatrix (double *arr1, double *arr2, unsigned int m, unsigned int n, double *res);
 void *subtractMatrix (double *arr1, double *arr2, unsigned int m, unsigned int n, double *res)
void multMatMat (double *A, double *B, int n, double *C);
void multMatArr (double *mat, double *v, int n, double *res);
double *multiplyMatrix(double *arr1, unsigned int m1, unsigned int n1,
          double *arr2, unsigned int m2, unsigned int n2);
double *transposeMatrix (double *arr, unsigned int n);
double *getDiagonal(double *arr, unsigned int m);
double *invDiagonal(double *arr, unsigned int m);
double maxN (double *arr, unsigned int m, unsigned int n);
double calculateNorm (double *A, double *b, double *x, int n, double *nTime);
double dotProduct (double *v1, double *v2, int n);
void scalarMult (double *v, int n, double k, double *r);




#endif //_GERAMAT_H