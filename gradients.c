/**
 * @file gradients.c
 * @brief Funções para calculo de gradientes conjugados
 */

#include <stdlib.h>
#include <stdio.h> 
#include <likwid.h>

#include "gradients.h"
#include "geraMat.h"
#include "utils.h"

  /***********************
 * @brief Resolve o sistema utilizando o Metodo dos Gradientes Conjugados
 * @param *A matriz contendo o sistema linear a ser calculado
 * @param *b matriz de termos independentes de A
 * @param n dimensao da matriz A
 * @param maxIt numero maximo de iterações
 * @param eps erro maximo admitido para o criterio de parada
 * @param n número de colunas da matriz original
 * @param *fp arquivo de saída
 ***********************/
double *conjugateGradients(double *A, double *B, unsigned int n, 
      unsigned int maxIt, double eps, FILE *fp) 
{
   double *At, *Ao, *Bo, *X, *Xn, *R, *R1, *R2, *V, *Z, 
   Rx[maxIt], aux, s, m, timePC = 0, timeIt,
          itTotal = 0, timeNorm = 0;
   int it = 0;
   
  // Ao = createTestMatrix(5,5);
  // Bo = createTestMatrix(5,5);
  // R1 = multiplyMatrix(Ao,5,5,Bo,5,5);
  // R2 = multiplyMatrixUaJ(Ao,5,5,Bo,5,5);
  // R = sumMatrix(Ao,Ao,5,5);
  // Xn = sumMatrix(R,R,5,5);
  // V = sumMatrix(Xn,Xn,5,5);
  // prnMat(Ao,5);
  // prnMat(R1,5);
  // prnMat(R2,5);
  // prnMat(V,5);
  // exit(0);
   
   /**** Operations for transforming the Matrix in a symmetric matrix *******/
   Ao = copyMatrix(A,n,n);
   Bo = copyMatrix(B,n,n);
   At = transposeMatrix(A, n, n);
   R1 = multiplyMatrix(At, n, n, A, n, n); 
   R2 = multiplyMatrix(At, n, n, B, n, 1); 
   free(A); free(B);
   A = copyMatrix(R1, n, n); // A = AT * A
   B = copyMatrix(R2, n, 1); // b = AT * b
   free(R1); free(R2);
   
   /*******************************************************************/
    
   X = generateZeroMatrix(n,1); //x(0) = 0
   R = copyMatrix(B, n, 1); // r = b
   R1 = multiplyMatrix(R, 1, n, R, n, 1); //rT*r
   aux = *R1; //aux = rT*r
   V = copyMatrix(B, n, 1); // v = b
  /*******************************************************************/
  
 /************************ Iteration *******************************/
           LIKWID_MARKER_INIT;
        LIKWID_MARKER_START("op1");


  for (int k = 0; k < maxIt; k++) {
      timeIt = timestamp();
      it++;
      Z = multiplyMatrix(A, n, n, V, n, 1); // z = A*v
      free(R1);
      R1 = multiplyMatrix(V, 1, n, Z, n, 1); //(vT * z)
      s = aux / *R1; //s = aux/(vT*z)
       
      *R1 = s; // Put the result of s in a 1x1 matrix to be multiplied
      R2 = multiplyMatrix(R1, 1, 1, V, 1, n); //(s * V);
      
      Xn = sumMatrix(X, R2, n, 1); // X(k+1) = X(k) + s*V
      
       
      free(R2);
      R2 = multiplyMatrix(R1, 1, 1, Z, 1, n);  //s*Z
      free(R1);
      R1 = copyMatrix(R, n, 1); //R1 = r
      free(R);
      R = subtractMatrix(R1, R2, n, 1); // r = r - sz
       
      free(R2);
      R2 = multiplyMatrix(R, 1, n, R, n, 1); //aux1 = rT * r
      Rx[it] = *R2;
      if (*R2 < eps) {
        
        double r = calculateNorm(Ao,Bo,Xn,n,&timeNorm);
        printOutput(r,timePC,timeNorm,it,itTotal,n,Rx,fp);
        return Xn; // Saída com  sol  =  x{k+l )
      }
      m = *R2/aux; // m = aux1/aux;
      aux = *R2; // aux = aux1
       
      *R2 = m; //Puting the value of m in an array to peform an operation with
               //matrices
      free(R1);
      R1 = multiplyMatrix(R2, 1, 1, V, 1, n); // (m * V)
      free(V);
      V = sumMatrix(R, R1, n, 1); // V = R + (m * V)
       
      free(X);
      X = copyMatrix(Xn, 1, n); // Prepare for next iteration X(k) = X(k+1)
      free(Xn); free(Z); free(R2);
      
      itTotal = itTotal + (timestamp() - timeIt);
  }
    /*******************************************************************/
    
    fprintf(fp, "\nErro! Sistema não converge!\n");
    fprintf(stderr, "Erro! Sistema não converge!\n");

}


 /***********************
 * @brief Resolve o sistema utilizando o Metodo dos Gradientes Conjugados com 
 *  pré condicionador
 * @param *A matriz contendo o sistema linear a ser calculado
 * @param *b matriz de termos independentes de A
 * @param *M matriz pré condicionadora
 * @param dimensao da matriz A
 * @param maxIt numero maximo de iterações
 * @param eps erro maximo admitido para o criterio de parada
 * @param n número de colunas da matriz original
 * @param *fp arquivo de saída
 ***********************/
double *preconditioningCg(double *A, double *B, double *M, unsigned int n, 
      unsigned int maxIt, double eps, FILE *fp) 
{

  double *At, *Ao, *Bo, *X, *Xn, *R, *R1, *R2, *V, *Z, *Y, 
  Rx[maxIt], aux, s, m, timePC = 0, timeIt,
        itTotal = 0, timeNorm = 0;
  int it = 0, cv = 0;
 
  /*** Operations for transforming the Matrix into a symmetric matrix *****/
  timePC = timestamp();
//  Ao = copyMatrix(A,n,n);
//  Bo = copyMatrix(B,n,n);
  At = transposeMatrix(A, n, n);
  R1 = multiplyMatrix(At, n, n, A, n, n); 
  R2 = multiplyMatrix(At, n, n, B, n, 1); 
  free(A); free(B);
  A = copyMatrix(R1, n, n); // A = AT * A
  B = copyMatrix(R2, n, 1); // b = AT * b
  free(R1); free(R2);
    /*******************************************************************/
  
  /*********** Invertion of the preconditioning matrix ****************/
  R1 = invDiagonal(M, n);
  free(M);
  M = copyMatrix(R1, n, n);
  free(R1);
  timePC = timestamp() - timePC;
  /*******************************************************************/
  
  X = generateZeroMatrix(n,1); //x(0) = 0
  R = copyMatrix(B, n, 1); // r = b
  V = multiplyMatrix(M, n, n, B, n, 1); // V = M^(-1) * b
  R1 = multiplyMatrix(V, 1, n, V, n, 1); //yT*r
  aux = *R1; //aux = yT*r
  /*******************************************************************/
  /************************ Iteration *******************************/
  for (int k = 0; k < maxIt; k++) {
    timeIt = timestamp();
      it++;
     
     	   LIKWID_MARKER_INIT;
        LIKWID_MARKER_START("op1"); 
      
      Z = multiplyMatrix(A, n, n, V, n, 1); // z = A*v
      
      free(R1);
      R1 = multiplyMatrix(V, 1, n, Z, n, 1); //(vT * z)
      s = aux / *R1; //s = aux/(vT*z)
      
      *R1 = s; // Put the result of s in a 1x1 matrix to be multiplied
      R2 = multiplyMatrix(R1, 1, 1, V, 1, n); //(s * V);
      Xn = sumMatrix(X, R2, n, 1); // X(k+1) = X(k) + s*V
      
      free(R2);
      R2 = multiplyMatrix(R1, 1, 1, Z, 1, n);  //s*Z
      free(R1); free(R);
      R1 = copyMatrix(R, n, 1); //R1 = r
      R = subtractMatrix(R1, R2, n, 1); // r = r - sz
      
      free(R2);
      R2 = multiplyMatrix(R, 1, n, R, n, 1); //aux1 =rT*r
      
      Y = multiplyMatrix(M, n, n, R, n, 1); // Y = M^(-1) * r
      

      Rx[it] = *R2;
      if (*R2 < eps) {
  cv = 1;
  break;
       //LIKWID_MARKER_START("marker-name");

       // double r = calculateNorm(A,B,Xn,n,&timeNorm);
        //LIKWID_MARKER_STOP("marker-name");
        
        //printOutput(r,timePC,timeNorm,it,itTotal,n,Rx,fp);
        //printMat(Xn,1,n,fp);
         //return Xn; // Saída com  sol  =  x{k+l )
      }
      
      R2 = multiplyMatrix(Y, 1, n, R, n, 1); //aux1 =yT*r
      
      m = *R2/aux; // m = aux1/aux;
      aux = *R2; // aux = aux1
      
      *R2 = m;  //Puting the value of m in an array to peform an operation with
      free(R1); //matrices
      R1 = multiplyMatrix(R2, 1, 1, V, 1, n); // m * V
      free(V);
      V = sumMatrix(Y, R1, n, 1); // V = y + (m * V)
      
      free(X);
      X = copyMatrix(Xn, 1, n); // Prepare for next iteration X(k) = X(k+1)
      free(Xn); free(Z); free(R2);
      itTotal = itTotal + (timestamp() - timeIt);
  }
    /*******************************************************************/
    LIKWID_MARKER_START("op2");

     double r = calculateNorm(A,B,Xn,n,&timeNorm);
    LIKWID_MARKER_STOP("op2");

    printOutput(r,timePC,timeNorm,it,itTotal,n,Rx,fp);
    printMat(Xn,1,n,fp);

    printf("# Tempo iter: %.15g sec \n", (itTotal/it) / 1000);
    printf("# Tempo residuo: %.15g sec \n", timeNorm/1000);

    if(!cv)
    {
      fprintf(fp, "\nErro! Sistema não converge!\n");
      fprintf(stderr, "Erro! Sistema não converge!\n");
    }
    LIKWID_MARKER_STOP("op1");
    LIKWID_MARKER_CLOSE;
    return Xn; // Saída com  sol  =  x{k+l )
    // exit(1);
}
