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
        
    }
}

char transpose_32_32_desc[] = "Transpose 32*32";
void transpose_32_32(int A[32][32],int B[32][32]){
    for(int i = 0;i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 8; k++){
                int v0 = A[i * 8 + k][j * 8];
                int v1 = A[i * 8 + k][j * 8 + 1];
                int v2 = A[i * 8 + k][j * 8 + 2];
                int v3 = A[i * 8 + k][j * 8 + 3];
                int v4 = A[i * 8 + k][j * 8 + 4];
                int v5 = A[i * 8 + k][j * 8 + 5];
                int v6 = A[i * 8 + k][j * 8 + 6];
                int v7 = A[i * 8 + k][j * 8 + 7];
                B[j * 8][i * 8 + k] = v0;
                B[j * 8 + 1][i * 8 + k] = v1;
                B[j * 8 + 2][i * 8 + k] = v2;
                B[j * 8 + 3][i * 8 + k] = v3;
                B[j * 8 + 4][i * 8 + k] = v4;
                B[j * 8 + 5][i * 8 + k] = v5;
                B[j * 8 + 6][i * 8 + k] = v6;
                B[j * 8 + 7][i * 8 + k] = v7;
            }
        }
    }    
}

char transpose_64_64_desc[] = "Transpose 64*64";
void transpose_64_64(int A[64][64],int B[64][64]){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 4; k++){
                int v0 = A[i * 4 + k][j * 4];
                int v1 = A[i * 4 + k][j * 4 + 1];
                int v2 = A[i * 4 + k][j * 4 + 2];
                int v3 = A[i * 4 + k][j * 4 + 3];
                B[j * 4][i * 4 + k] = v0;
                B[j * 4 + 1][i * 4 + k] = v1;
                B[j * 4 + 2][i * 4 + k] = v2;
                B[j * 4 + 3][i * 4 + k] = v3;
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

