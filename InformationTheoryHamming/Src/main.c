#include <stdio.h>
#include "../Inc/Hamming.h"

int main() {
	// Default H matrix
	int H[3][7] =  {{1,0,0,1,0,1,1},
			{0,1,0,1,1,0,1},
			{0,0,1,0,1,1,1}};

	// Generator matrix G
	int G[K][N-K];
	generateGeneratorMatrix(K, N, H, G);

	// Print the generator matrix G
	printf("Generator Matrix G:\n");
	printMatrix(K, N, resultMatrix);


	// Generate and print code words
	int codeWords[1 << K][N];
	generateXORMatrix(K,resultMatrix,codeWords);

	printf("\nGenerated Code Words:\n");
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < N; ++j) {
			printf("%d ", codeWords[i][j]);
		}
		printf("\n");
	}

	// Print Transmitted code word
	getCodeWord();
	printf("\nThe Transmitted Code :\n");
	for(int i=0; i<7; i++)
	{
		printf("%d ",sentCodeWord[i]);
	}

	// Introduce errors (flip one bit)
	int errorPattern[7] = {0, 0, 0, 1, 0, 0, 0};
	printf("\nError Pattern: \n");
	for(int i=0; i<N; i++)
	{
		printf("%d ",errorPattern[i]);
	}
	for (int i = 0; i < N; ++i) {
		sentCodeWord[i] ^= errorPattern[i];
	}

	// Print the transmitted code word after error
	printf("\nTransmitted Code Word with Error:\n");
	for (int i = 0; i < N; ++i) {
		printf("%d ", sentCodeWord[i]);
	}


	// Find H Transpose and print it
	int Ht[N][N-K];
	transposeMatrix(N-K,N,H,Ht);
	printf("\nH transpose:\n");
	printMatrix(N,N-K,Ht);

	// Syndrome calculation
	int syndrome[N-K];
	for (int i = 0; i < N - K; ++i) {
		syndrome[i] = 0;
		for (int j = 0; j < N; ++j) {
			syndrome[i] ^= Ht[j][i] & sentCodeWord[j];
		}
	}

	// Print Syndrome
	printf("\nSyndrome:\n");
	for (int i = 0; i < N - K; ++i) {
		printf("%d ", syndrome[i]);
	}

	//Correct the corrupted bit in the received word
	int matched = 0;
	for(int i =0; i < N; i++)
	{
		matched = 0;
		for(int j=0; j<N - K; j++)
		{
			if(syndrome[j] == Ht[i][j])
			{
				matched++;
			}
		}
		if(matched == 3)
		{
			sentCodeWord[i] ^= 1;
			break;
		}
	}
	//Print corrected received code word
	printf("\nReceived Code Word after correction:\n");
	for (int i = 0; i < N; ++i) {
		printf("%d ", sentCodeWord[i]);
	}

	//Remove additional bits and print the original message
	printf("\nOriginal message:\n");
	for(int i = N-K;i<N; i++)
	{
		printf("%d ",sentCodeWord[i]);
	}

	return 0;
}
