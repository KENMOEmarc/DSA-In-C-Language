//Inversion Matricielle.

#include<stdio.h>
#define N 3

int main (){
	int  j, i, L, Col;
	float M[N][N];
	float a, b, c, e, f, g, h, k, d;
	float Det, I;
	
	printf("Remplissez la matrice \n");
	

	
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++)
		{
			printf("Saisissez l'element %d %d :",i, j);
			scanf("%f",&M[i][j]);
		}
		printf("\n");
	}
	
	printf("Matrice originelle \n");
	
	for (i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			printf(" %f",M[i][j]);
		}
	printf("\n");
		
	}
	
	printf("Determinant:\n");
	
	Det = M[0][0] * ( M[1][1] * M[2][2] - M[1][2] * M[2][1] );
	Det = Det - M[0][1] * ( M[1][0] * M[2][2] - M[1][2] * M[2][0] );
	Det = Det + M[0][2] * ( M[1][0] * M[2][1] - M[1][1] * M[2][0] );
// Matrix Inversion Program
// This program computes the inverse of a 3x3 matrix using the adjugate method.
// It reads the matrix from user input, calculates the determinant, and if invertible,
// computes the cofactor matrix, transposes it to get the adjugate, and scales by 1/det to get the inverse.

#include <stdio.h>

#define N 3  // Size of the matrix (fixed to 3x3)

int main() {
    int i, j;  // Loop indices
    float matrix[N][N];  // Original matrix
    float cofactor[N][N];  // Cofactor matrix
    float inverse[N][N];  // Inverse matrix
    float det;  // Determinant
    float inv_det;  // 1 / determinant

    // Prompt user to fill the matrix
    printf("Fill the matrix\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("Enter element %d %d: ", i, j);
            scanf("%f", &matrix[i][j]);
        }
        printf("\n");
    }

    // Print the original matrix
    printf("Original matrix:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf(" %f", matrix[i][j]);
        }
        printf("\n");
    }

    // Compute the determinant using the 3x3 formula
    det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
    det -= matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
    det += matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    // Print the determinant
    printf("Determinant: %f\n", det);

    // Check if the matrix is invertible
    if (det == 0) {
        printf("This matrix is not invertible.\n");
    } else {
        printf("This matrix can be inverted.\n");

        // Compute 1 / determinant
        inv_det = 1.0 / det;

        // Compute the cofactor matrix (without overwriting original)
        // Cofactor C_ij = (-1)^{i+j} * det(minor_ij)
        cofactor[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
        cofactor[0][1] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
        cofactor[0][2] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        cofactor[1][0] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
        cofactor[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]);
        cofactor[1][2] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
        cofactor[2][0] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]);
        cofactor[2][1] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
        cofactor[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);

        // Print the cofactor matrix for reference
        printf("Cofactor matrix:\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf(" %f", cofactor[i][j]);
            }
            printf("\n");
        }

        // Compute the inverse: inverse[i][j] = inv_det * cofactor[j][i] (adjugate is transpose of cofactor)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                inverse[i][j] = inv_det * cofactor[j][i];
            }
        }

        // Print the inverse matrix
        printf("Inverse matrix:\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf(" %f", inverse[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
