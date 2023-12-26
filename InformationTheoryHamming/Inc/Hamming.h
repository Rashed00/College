/*
 * Hamming.h
 *
 *  Created on: 26 Dec 2023
 *      Author: Rashed
 */

#ifndef INC_HAMMING_H_
#define INC_HAMMING_H_

#include <stdio.h>
#include <math.h>

#define K 	4	// Number of data bits
#define N 	7	// Total number of bits in code words



extern int resultMatrix[K][N];
extern int defaultDataBits[K];
extern int sentCodeWord[N];

void getCodeWord();
void generateXORMatrix(int X, int matrix[X][N], int result[][N]);
void transposeMatrix(int rows, int cols, int matrix[][cols], int result[][rows]);
void concatenateMatrices(int rows, int cols1, int matrix1[][cols1], int cols2, int matrix2[][cols2], int result[][cols1 + cols2]);
void createIdentityMatrix(int size, int identityMatrix[][size]);
void generateGeneratorMatrix(int k, int n, int H[][n], int G[][n - k]);
void printMatrix(int rows, int cols, int matrix[][cols]);

#endif /* INC_HAMMING_H_ */
