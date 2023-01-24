
/*
 * Add your unoptimized implementation here
 */

#include "utils.h"
#define CHUNK_SIZE 40


void multiply_B_A(register int N, double *A, double* B, double* C) {


        int i; 
	register int j, k;

        for (i = 0; i < N; i++) {
		register double *c_ptr = C + i *N;
		double *b_org = B + i * N;
                for (j = 0; j < N; j++) {
			register double *b = b_org;
			register double *a = A + j;
			register double sum = 0.0;
                        for (k = 0; k <= j; k++) {
                                sum += *b * *a;
				a += N;
				b++;
                        }
			*c_ptr += sum;
			c_ptr++;

                }
        }

}

void multiply_B_A_At(register int N, double* BA, double* A, double* C) {

       int i;
       register int j, k;

        for (i = 0; i < N; i++) {
		register double *c_ptr = C + i * N;
		double *ba_org = BA + i * N;
                for (j = 0; j < N; j++) {
			register double *ba = ba_org + j;
			register double *a = A + j * N +j;
			register int stop_index = N - j - CHUNK_SIZE;
			register double sum = 0.0;
                        for (k = 0; k < stop_index; k+= CHUNK_SIZE) {
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;

                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;

                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                
				sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;

                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                                sum += *ba * *a; ba++; a ++;
                        }
			stop_index += CHUNK_SIZE;
			for(;k<stop_index; k++){
				sum += *ba * *a; ba++; a ++;
			}
			*c_ptr += sum;
			c_ptr++;
                }
        }

}


void multiply_Bt_B(register int N, double* B, double* C) {

        int i, j; 
	register int k;

        for (i = 0; i < N; i++) {
		double *bt_org = B + i;
		register double *c_ptr = C + i *N;
                for (j = 0; j < N; j++) {
			register double *bt = bt_org;
			register double *b = B + j;
			register double sum = 0.0;
                        for (k = 0; k < N; k ++) {
                               sum += *bt * *b; bt += N; b += N;

                        }
			*c_ptr += sum;
			c_ptr++;
                }
        }

}
double* my_solver(int N, double *A, double* B) {
        printf("OPT SOLVER\n");


        double *temp1 = (double *)calloc(N * N, sizeof(double));

        double *temp2 = (double *)calloc(N * N, sizeof(double));

        double *temp3 = (double *)calloc(N * N, sizeof(double));

       	double *C = (double *)calloc(N * N, sizeof(double));
        
	if (!temp1 || !temp2 || !temp3 || !C)
                return NULL;



        register int i,j;
        multiply_B_A(N, A, B, temp1);
        multiply_B_A_At(N, temp1, A, temp2);
        multiply_Bt_B(N, B, temp3);

        for(i = 0; i<N; i++){
		register double *temp2_ptr = temp2 + N * i;
		register double *temp3_ptr = temp3 + N * i;
		register double *c_ptr = C + N *i;
                for(j = 0 ; j<N; j++){
                        *c_ptr += *temp2_ptr + *temp3_ptr;
			c_ptr++;
			temp2_ptr++;
			temp3_ptr++; 
                }
        }

        free(temp1);
        free(temp2);
        free(temp3);

        return C;
}
