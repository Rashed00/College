/*
 * Hamming.c
 *
 *  Created on: 26 Dec 2023
 *      Author: Rashed
 */

#include "../Inc/Hamming.h"


int resultMatrix[K][N];
int defaultDataBits[K] = {1, 0, 1, 0};
int sentCodeWord[N] = {0, 0, 0, 0, 0, 0, 0};

void getCodeWord() {
	// Function implementation
	for(int i=0; i <7; i++ )
	{
		for(int j =0; j <4; j++)
		{
			sentCodeWord[i] ^= (defaultDataBits[j] * resultMatrix[j][i]);
		}
	}
}

void generateXORMatrix(int X, int matrix[X][N], int result[][N]) {
	// Function implementation
	int numRows = (1<<X);
	int numCols = 7;

	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			result[i][j] = matrix[i][j];
		}
	}

	int rowIdx = X;
	for (int i = 0; i < X; ++i) {
		for (int j = i + 1; j < X; ++j) {
			for (int k = 0; k < numCols; ++k) {
				result[rowIdx][k] = matrix[i][k] ^ matrix[j][k];
			}
			++rowIdx;
		}
	}
}

void transposeMatrix(int rows, int cols, int matrix[][cols], int result[][rows]) {
	// Function implementation
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			result[j][i] = matrix[i][j];
		}
	}
}

void concatenateMatrices(int rows, int cols1, int matrix1[][cols1], int cols2, int matrix2[][cols2], int result[][cols1 + cols2]) {
	// Function implementation
	for (int i = 0; i < rows; ++i) {
		// Copy elements from the first matrix
		for (int j = 0; j < cols1; ++j) {
			result[i][j] = matrix1[i][j];
		}

		// Copy elements from the second matrix
		for (int j = 0; j < cols2; ++j) {
			result[i][cols1 + j] = matrix2[i][j];
		}
	}
}

void createIdentityMatrix(int size, int identityMatrix[][size]) {
	// Function implementation
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			identityMatrix[i][j] = (i == j) ? 1 : 0;
		}
	}
}

void generateGeneratorMatrix(int k, int n, int H[][n], int G[][n - k]) {
	// Function implementation
	int size = k;
	int identityMatrix[size][size];
	int parityIndex = 3;
	// Transpose of the H matrix to obtain G
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			G[j][i] = H[i][parityIndex];
			parityIndex++;
		}
		parityIndex = 3;
	}
	createIdentityMatrix(size,identityMatrix);
	concatenateMatrices(size,n-k,G,k,identityMatrix,resultMatrix);
}

void printMatrix(int rows, int cols, int matrix[][cols]) {
	// Function implementation
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}


