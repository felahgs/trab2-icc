/**
 * @file geraMat.c
 * @brief Criação e Operação com matrizes
 */
// #define DBL_FIELD "%9.2lg"
#define DBL_FIELD  "%9.2lg"
#define ROLL 4
// #define DBL_FIELD "%12.7lg"
#define SEP_RES "\n\n"
#define MAT(m,cols,i,j)   m[(i)*(cols)+(j)] 

#ifndef __GERAMAT_H__
#define __GERAMAT_H__

//Geradores de coeficientes
double generateRandomA( unsigned int i, unsigned int j, unsigned int k );
double generateRandomB( unsigned int k );

//Geradores de Matrizes
double *createTestMatrix (unsigned int m, unsigned int n);
double *generateZeroMatrix(unsigned int m, unsigned int n);
double *generateBandMatrix (unsigned int k, unsigned int n);
double *generateIndTerms (unsigned int n, unsigned int k);

//Operações Com Matrizes
double *copyMatrix (double *arr, unsigned int m, unsigned int n);
double *sumMatrix (double *arr1, double *arr2, unsigned int m, unsigned int n);
double *subtractMatrix (double *arr1, double *arr2, unsigned int m, unsigned int n);
double *multiplyMatrix(double *arr1, unsigned int m1, unsigned int n1,
          double *arr2, unsigned int m2, unsigned int n2);
double *transposeMatrix (double *arr,unsigned int m, unsigned int n);
double *getDiagonal(double *arr, unsigned int m);
void prnMat (double *mat, int n);
void prnArr (double *vet, int n);
double dotProduct (double *v1, double *v2, int n);
 double calculateNorm (double *A, double *b, double *x, int n, double *nTime);
 void multMatMat (double *A, double *B, int n, double *C);
 double *invDiagonal(double *arr, unsigned int m);
 double *multMatVet (double *mat, double *v, int m, int n);
 double *multiplyMatrixUaJ(double *arr1, unsigned int m1, unsigned int n1,
          double *arr2, unsigned int m2, unsigned int n2);
double dotProduct (double *v1, double *v2, int n);
void scalarMult (double *v, int n, double k, double *r);
void multMatMat (double *A, double *B, int n, double *C);




#endif //_GERAMAT_H