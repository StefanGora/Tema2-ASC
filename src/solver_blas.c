/*
 * Tema 2 ASC
 * 2022 Spring
 */

/* 
 * Add your BLAS implementation here
 */

#include "utils.h"
#include "cblas.h"

double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");

	double *B_A = (double *)calloc(N * N, sizeof(double));

	double *C = (double *)calloc(N * N, sizeof(double));

	if(!A || !B || !B_A || !C)
		return NULL;

//C=B*A*At+Bt*B

//compute Bt * B
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1.0, B, N, B, N, 1.0, C, N);
//compute B * A
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, B, N, A, N, 1.0, B_A, N);
//compute B * A * At	
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, B_A, N, A, N, 1.0, C, N);

	free(B_A);
	return C;
}
