/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */


void multiply_B_A(int N, double *A, double* B, double* C) {

	if(!A || !B || !C)
        return;

	int i = 0, j = 0, k = 0;

	for (i = 0; i < N; i++) 
		for (j = 0; j < N; j++) 
			for (k = 0; k <= j; k++) 
				C[i * N + j] += B[i * N + k] * A[k * N + j];

}

void multiply_B_A_At(int N, double* BA, double* A, double* C) {

	if(!BA || !A || !C)
        return;


	int i = 0, j =0, k = 0;

	for (i = 0; i < N; i++) 
		for (j = 0; j < N; j++) 
			for (k = 0; k < N -j; k++) 
				C[i * N + j] += BA[i * N + k + j] * A[j * N + j + k];
			
}


void multiply_Bt_B(int N, double* B, double* C) {

	if(!B || !C)
        return;

	int i = 0, j = 0, k = 0;

	for (i = 0; i < N; i++) 
		for (j = 0; j < N; j++) 
			for (k = 0; k < N; k++) 
				C[i * N + j] += B[k * N + i] * B[k * N + j];

}



double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");


	double *temp1 = (double *)calloc(N * N, sizeof(double));

	double *temp2 = (double *)calloc(N * N, sizeof(double));

	double *temp3 = (double *)calloc(N * N, sizeof(double));

	double *C = (double *)calloc(N * N, sizeof(double));

	if(!A || !B || !temp1 || !temp2 || !temp3 || !C)
        return NULL;


	int i,j = 0;	
	multiply_B_A(N, A, B, temp1);
	multiply_B_A_At(N, temp1, A, temp2);
	multiply_Bt_B(N, B, temp3);

	for(i = 0; i<N; i++)
		for(j = 0 ; j<N; j++)
			C[i * N + j] = (double)temp2[i * N + j] + (double)temp3[i * N + j];
		
	free(temp1);
	free(temp2);
	free(temp3);

	return C;
	
}
