/**
 * @file gradients.c
 * @brief Funções para calculo de gradientes conjugados
 */

#include <stdlib.h>
#include <stdio.h> 

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
double *conjugateGradients(double *Ao, double *Bo, unsigned int n, 
      unsigned int maxIt, double eps, FILE *fp) 
{
   double *At, *X, *Xn, *R, *Vs, *Zs, *V, *Z, 
            *A, *B,
            *R3, *R4,
            aux, aux1, s, m, timePC = 0, timeIt,
            itTotal = 0, timeNorm = 0;
   int it = 0;
   
   /**** Operations for transforming the Matrix in a symmetric matrix *******/
   At = transposeMatrix(Ao, n);
   A = multiplyMatrix(At, n, n, Ao, n, n); 
   B = multiplyMatrix(At, n, n, Bo, n, 1); 
//   free(A); free(B);
//   A = copyMatrix(R1, n, n); // A = AT * A
//   B = copyMatrix(R2, n, 1); // b = AT * b
//   free(R1); 
    // prnMat(A,n);
    // prnArr(B,n);
    /*--------------------MULTIPLICATION FUNCTION TEST-------------------*/
    // R1 = createTestMatrix(1,3);
    // R2 = createTestMatrix(1,3);
    // // // R3 = multiplyMatrix(R1, 5, 5, R2, 5, 5);
    // R3 = newMatrix(1,3);
    
    // // // mmm(R2,R2,5,R3);
    // prnArr(R1,3);
    // sumMatrix(R1, R1, 1, 3, R2);
    // sumMatrix(R2, R2, 1, 3, R2);
    
    // prnMat(R1,3);
    // prnArr(R2,3);
    // scalarMult(R2,3,2);
    // prnArr(R2,3);
    // multMatArr(R1,R2,3,R3);
    // prnArr(R3, 3);
    
    // double dot = dotProduct(R1,R2,20);
    // printf("%12.7lg\n", dot);
    
    // free(R1); free(R2); free(R3);
    
    /*-------------------------------------------------------------------*/
    
    
   /*******************************************************************/
    
   X = newMatrix(n,1); //x(0) = 0
   
   R = newMatrix(n,1);
   copyMatrix(B, n, 1, R); // r = b
   
   aux = dotProduct(R,R,n); //aux = rT*r
  // prnArr(R,n); printf("%12.7lg\n", aux);
   
   V = newMatrix(n, 1);
   Vs = newMatrix(n, 1);
   copyMatrix(B, n, 1, V); // v = b
   
   Z = newMatrix(n, 1);
   Zs = newMatrix(n, 1);
   Xn = newMatrix(n, 1);
  /*******************************************************************/
  
 /************************ Iteration *******************************/
  for (int k = 0; k < maxIt; k++) {
      timeIt = timestamp();
      it++;
       
    //   free(Z);
      Z = newMatrix(1,n);
      multMatArr(A,V,n,Z);  // z = A*v
    //   printf("%d: ", it); prnMat(A,n); 
    //   printf("It-%d V: ", it); prnArr(V,n);
    //   printf("It-%d Z: ", it); prnArr(Z,n);
    //   printf("It-%d: ", it); prnArr(Z,n); printf("%12.7lg\n", s);
      s = (aux / dotProduct(V,Z,n)); //s = aux/(vT*z)
      scalarMult(V,n,s, Vs); //(s * V);
      
      
      sumMatrix(X, Vs, n, 1, Xn); // X(k+1) = X(k) + s*V
      scalarMult(Z, n, s, Zs); // s*Z
      
      subtractMatrix(R, Zs, n, 1, R); // r = r - sz
      aux1 = dotProduct(R,R,n); //aux1 = rT * r
      // printf("%12.7lg\n", aux1); 
      fprintf(fp, "# iter %d: %.15g\n",  it, aux1);
      if (aux1 < eps) {
        
        double r = calculateNorm(A,B,Xn,n,&timeNorm);
        
        fprintf(fp, "# Residuo: %.15g \n", r);
        fprintf(fp, "# Tempo PC: %.15g sec \n", (timePC / 1000));
        fprintf(fp, "# Tempo iter: %.15g sec \n", (itTotal/it) / 1000);
        fprintf(fp, "# Tempo residuo: %.15g sec \n", timeNorm/1000);
        fprintf(fp, "# \n");
        fprintf(fp,"%d\n", n);
        printMat(Xn,1,n,fp);
        return Xn; // Saída com  sol  =  x{k+l )
      }
      m = aux1/aux; // m = aux1/aux;
      aux = aux1; // aux = aux1
       
      scalarMult(V,n,m,Vs); // (m*V)
      sumMatrix(R, Vs, n, 1, V); // V = R + (m * V)
       
      copyMatrix(Xn, 1, n, X); // Prepare for next iteration X(k) = X(k+1)
      
    //   printf("It-%d: ", it); prnArr(X,n); exit(0); 
      itTotal = itTotal + (timestamp() - timeIt); 
    //   printf("It-%d: ", it); prnArr(Z,n); printf("%12.7lg\n", s);
  }
    /*******************************************************************/
    double r = calculateNorm(A,B,Xn,n,&timeNorm);
    
    fprintf(fp, "# Residuo: %.15g \n", r);
    fprintf(fp, "# Tempo PC: %.15g sec \n", (timePC / 1000));
    fprintf(fp, "# Tempo iter: %.15g sec \n", (itTotal/it) / 1000);
    fprintf(fp, "# Tempo residuo: %.15g sec \n", timeNorm/1000);
    fprintf(fp, "# \n");
    fprintf(fp,"%d\n", n);
    fprintf(fp, "\nErro! Sistema não converge!\n");
    fprintf(stderr, "Erro! Sistema não converge!\n");
    // exit(1);
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
// double *preconditioningCg(double *A, double *B, double *M, unsigned int n, 
//       unsigned int maxIt, double eps, FILE *fp) 
// {
//   double *At, *X, *Xn, *R, *R1, *R2, *V, *Z, *Y, aux, s, m, timePC = 0, timeIt,
//       itTotal = 0, timeNorm = 0;
//   int it = 0;
   
//   /*** Operations for transforming the Matrix into a symmetric matrix *****/
//   timePC = timestamp();
//   At = transposeMatrix(A, n);
//   R1 = multiplyMatrix(At, n, n, A, n, n); 
//   R2 = multiplyMatrix(At, n, n, B, n, 1); 
//   free(A); free(B);
//   A = copyMatrix(R1, n, n); // A = AT * A
//   B = copyMatrix(R2, n, 1); // b = AT * b
//   free(R1); free(R2);

  
//   /*********** Invertion of the preconditioning matrix ****************/
//   R1 = invDiagonal(M, n);
//   free(M);
//   M = copyMatrix(R1, n, n);
//   free(R1);
//   timePC = timestamp() - timePC;
//   /*******************************************************************/
  
//   X = newMatrix(n,1); //x(0) = 0
//   R = copyMatrix(B, n, 1); // r = b
//   V = multiplyMatrix(M, n, n, B, n, 1); // V = M^(-1) * b
//   R1 = multiplyMatrix(V, 1, n, V, n, 1); //yT*r
//   aux = *R1; //aux = yT*r

   
//   /************************ Iteration *******************************/
//   for (int k = 0; k < maxIt; k++) {
//     timeIt = timestamp();
//       it++;
      
//       Z = multiplyMatrix(A, n, n, V, n, 1); // z = A*v
      
//       free(R1);
//       R1 = multiplyMatrix(V, 1, n, Z, n, 1); //(vT * z)
//       s = aux / *R1; //s = aux/(vT*z)
      
//       *R1 = s; // Put the result of s in a 1x1 matrix to be multiplied
//       R2 = multiplyMatrix(R1, 1, 1, V, 1, n); //(s * V);
//       Xn = sumMatrix(X, R2, n, 1); // X(k+1) = X(k) + s*V
      
//       free(R2);
//       R2 = multiplyMatrix(R1, 1, 1, Z, 1, n);  //s*Z
//       free(R1); free(R);
//       R1 = copyMatrix(R, n, 1); //R1 = r
//       R = subtractMatrix(R1, R2, n, 1); // r = r - sz
      
//       free(R2);
//       R2 = multiplyMatrix(R, 1, n, R, n, 1); //aux1 =rT*r
      
//       Y = multiplyMatrix(M, n, n, R, n, 1); // Y = M^(-1) * r
      
//       // printf("R2 %0.8f iteration:%d \n", *R2, it);
//       fprintf(fp, "# iter %d: %.15g\n",  it, *R2);

//       if (*R2 < eps) {
//         double r = calculateNorm(A,B,Xn,n,&timeNorm);
        
//         fprintf(fp, "# Residuo: %.15g \n", r);
//         fprintf(fp, "# Tempo PC: %.15g sec \n", (timePC / 1000));
//         fprintf(fp, "# Tempo iter: %.15g sec \n", (itTotal/it) / 1000);
//         fprintf(fp, "# Tempo residuo: %.15g sec \n", timeNorm/1000);
//         fprintf(fp, "# \n");
//         fprintf(fp,"%d\n", n);
//         printMat(Xn,1,n,fp);
//          return Xn; // Saída com  sol  =  x{k+l )
//       }
      
//       R2 = multiplyMatrix(Y, 1, n, R, n, 1); //aux1 =yT*r
      
//       m = *R2/aux; // m = aux1/aux;
//       aux = *R2; // aux = aux1
      
//       *R2 = m;  //Puting the value of m in an array to peform an operation with
//       free(R1); //matrices
//       R1 = multiplyMatrix(R2, 1, 1, V, 1, n); // m * V
//       free(V);
//       V = sumMatrix(Y, R1, n, 1); // V = y + (m * V)
      
//       free(X);
//       X = copyMatrix(Xn, 1, n); // Prepare for next iteration X(k) = X(k+1)
//       free(Xn); free(Z); free(R2);
//       itTotal = itTotal + (timestamp() - timeIt);
//   }
//     /*******************************************************************/
    
//     fprintf(fp, "\nErro! Sistema não converge!\n");
//     fprintf(stderr, "Erro! Sistema não converge!\n");   
//     exit(1);
// }