/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void transpose_32_32(int A[32][32],int B[32][32]);
void transpose_64_64(int A[64][64],int B[64][64]);
void transpose_any(int M,int N, int A[N][M],int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]){
    if(M == 32 && N == 32){
        transpose_32_32(A,B);
    }
    else if(M == 64 && N == 64){
        transpose_64_64(A,B);
    }
    else{
        transpose_any(M,N,A,B);
    }
}

void transpose_32_32(int A[32][32],int B[32][32]){
    for(int i = 0; i < 32; i += 8){
        for(int j = 0; j < 32; j += 8){
            for(int k = 0; k < 8; k++){
                int v0 = A[i + k][j];
                int v1 = A[i + k][j + 1];
                int v2 = A[i + k][j + 2];
                int v3 = A[i + k][j + 3];
                int v4 = A[i + k][j + 4];
                int v5 = A[i + k][j + 5];
                int v6 = A[i + k][j + 6];
                int v7 = A[i + k][j + 7];
                B[j][i + k] = v0;
                B[j + 1][i + k] = v1;
                B[j + 2][i + k] = v2;
                B[j + 3][i + k] = v3;
                B[j + 4][i + k] = v4;
                B[j + 5][i + k] = v5;
                B[j + 6][i + k] = v6;
                B[j + 7][i + k] = v7;
            }
        }
    }    
}

void transpose_64_64(int A[64][64],int B[64][64]){
    int i,j,k;
    int v0,v1,v2,v3,v4,v5,v6,v7;
    for(i = 0; i < 64; i += 8){
        for(j = 0; j < 64; j += 8){
            for(k = 0; k < 4; k++){
                v0 = A[i + k][j];
                v1 = A[i + k][j + 1];
                v2 = A[i + k][j + 2];
                v3 = A[i + k][j + 3];
                v4 = A[i + k][j + 4];
                v5 = A[i + k][j + 5];
                v6 = A[i + k][j + 6];
                v7 = A[i + k][j + 7];

                B[j][i + k] = v0;
                B[j + 1][i + k] = v1;
                B[j + 2][i + k] = v2;
                B[j + 3][i + k] = v3;

                B[j][i + k + 4] = v4;
                B[j + 1][i + k + 4] = v5;
                B[j + 2][i + k + 4] = v6;
                B[j + 3][i + k + 4] = v7;
            }

            for(k = 0; k < 4; k++){
                v0 = A[i + 4][j + k];
                v1 = A[i + 5][j + k];
                v2 = A[i + 6][j + k];
                v3 = A[i + 7][j + k];
                
                v4 = B[j + k][i + 4];
                v5 = B[j + k][i + 5];
                v6 = B[j + k][i + 6];
                v7 = B[j + k][i + 7];

                B[j + k][i + 4] = v0;
                B[j + k][i + 5] = v1;
                B[j + k][i + 6] = v2;
                B[j + k][i + 7] = v3;

                B[j + k + 4][i] = v4;
                B[j + k + 4][i + 1] = v5;
                B[j + k + 4][i + 2] = v6;
                B[j + k + 4][i + 3] = v7;
            }

            for(k = 4; k < 8; k++){
                v0 = A[i + k][j + 4];
                v1 = A[i + k][j + 5];
                v2 = A[i + k][j + 6];
                v3 = A[i + k][j + 7];

                B[j + 4][i + k] = v0;
                B[j + 5][i + k] = v1;
                B[j + 6][i + k] = v2;
                B[j + 7][i + k] = v3;

            }
        }
    }    
}

char transpose_any_desc[] = "Transpose any shape";
void transpose_any(int M,int N, int A[N][M],int B[M][N]){
    const int STEP = 17;
    int i,j,r,c;
    for(i = 0; i < N; i += STEP){
        for(j = 0; j < M; j += STEP){
            for(r = i; r < i + STEP && r < N; r++){
                for(c = j; c < j + STEP && c < M; c++){
                    B[c][r] = A[r][c];
                }
            }
        }
    }
}


char transpose_desc[] = "Transpose Simply";
void transpose(int M,int N,int A[N][M],int B[M][N]){
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N;j++){
            B[i][j] = A[j][i];
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    registerTransFunction(transpose, transpose_desc); 
    registerTransFunction(transpose_any, transpose_any_desc); 


}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

