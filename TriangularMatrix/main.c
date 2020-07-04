#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
typedef struct
{
    int dim;
    int* data;
} UpperTriangularMatrix;
/*
 * initUpperTriangularMatrix
 *		- creates a new matrix
 *		- initializes the matrix by allocating enough memory
 */
UpperTriangularMatrix initUpperTriangularMatrix(int dim)
{
    UpperTriangularMatrix mat;
    mat.dim=dim;
    mat.data=malloc(sizeof(int)*(dim*(dim+1)/2));
    /* TODO: ADD YOUR CODE HERE */
    return mat;
}
/*
 * destroyUpperTriangularMatrix
 *		- frees the allocated memory
 *		- set dim to zero
 */
void destroyUpperTriangularMatrix(UpperTriangularMatrix *mat)
{


    mat->dim=0;
    free(mat->data);

    /* TODO: ADD YOUR CODE HERE */
}
/*
 * get: returns the item at mat[row][col]
 */
int get(UpperTriangularMatrix mat, int row, int col)
{ if(row<=col){

    int value=mat.data[(col*(col+1))/2+row];

    return value;}
else

    /* TODO: ADD YOUR CODE HERE */
    return 0;
}
/*
 * set: assigns mat[row][col] to val
 */
int set(UpperTriangularMatrix mat, int row, int col, int val)
{
    assert(row<=col || val==0);

    mat.data[(col*(col+1))/2+row]=val;





}


/* TODO: ADD YOUR CODE HERE */

/*
 * addTriangularMatrices:
 *			sum = mat1 + mat2;
 */
UpperTriangularMatrix addTriangularMatrices(UpperTriangularMatrix mat1, UpperTriangularMatrix mat2)
{
    assert(mat1.dim == mat2.dim);
    UpperTriangularMatrix sum= initUpperTriangularMatrix(mat1.dim);
int dim=(mat1.dim*(mat1.dim+1)/2);
for(int i=0;i<dim;i++){

sum.data[i]=mat1.data[i]+mat2.data[i];
}
    /* TODO: ADD YOUR CODE HERE */
    return sum;
}
/*
 * convertFileToUpperTriangularMatrix
 *			assumes file format as follows:
 *			- first line contains dimensions
 *			- each row in a line
 *			- each row contains elements in the upper triangle only, space separated
 */
UpperTriangularMatrix convertFileToUpperTriangularMatrix(char* filename)
{
    UpperTriangularMatrix mat;
    int dim, val;
    int i, j;
    char line[512], *token;

    FILE *fp = fopen(filename, "r");

    assert(fp != NULL);

    fscanf(fp, "%d\n", &dim);

    mat = initUpperTriangularMatrix(dim);

    for(i=0; i<mat.dim; i++)
        for(j=i; j<mat.dim; j++)
        {
            fscanf(fp, "%d", &val);
            set(mat, i, j, val);
        }

    fclose(fp);
    return mat;
}
/*
 *
 */
void printMatrix(char* title, UpperTriangularMatrix mat)
{
    int i, j;

    printf("%s\n", title);

    for(i=0; i<mat.dim; i++)
    {
        for(j=0; j<mat.dim; j++)
            printf("%5d  ", get(mat, i, j));
        printf("\n");
    }

    printf("...................................................\n");
}
/*
 *
 */
void main(int argc, char**argv)
{
    if(argc!=3)
    {
        printf("Usage: %s file1 file2\n", argv[0]);
        exit(1);
    }
    UpperTriangularMatrix matA = convertFileToUpperTriangularMatrix(argv[1]);
    printMatrix("Matrix A\n========", matA);
    UpperTriangularMatrix matB = convertFileToUpperTriangularMatrix(argv[2]);
    printMatrix("Matrix B\n========", matB);

    UpperTriangularMatrix matC = addTriangularMatrices(matA, matB);
    printMatrix("Matrix C = A + B\n================", matC);

    destroyUpperTriangularMatrix(&matA);
    printMatrix("Matrix A (after destroy)\n========================", matA);
    destroyUpperTriangularMatrix(&matB);
    printMatrix("Matrix B (after destroy)\n========================", matB);
    destroyUpperTriangularMatrix(&matC);
    printMatrix("Matrix C (after destroy)\n========================", matC);

    return 0;
}
