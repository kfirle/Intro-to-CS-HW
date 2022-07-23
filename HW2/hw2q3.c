#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 25

void print_welcome_message1(){
	printf("Starting the AES Algorithm, please pick amount of iterations:\n");
}

void print_invalid_amount(){
	printf("Invalid amount of iterations!\n");
	printf("Please try again:\n");
}

void print_welcome_message2(){
	printf("Please pick a matrix size:\n");
}

void print_enter_matrix(){
	printf("Please enter the matrix:\n");
}

void print_encrypted_message(){
	printf("The encrypted message is:\n");
}

void print_matrix(int n, int aes[N][N]){
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", aes[i][j]);
		}
		printf("\n");
	}
}

void build_matrix(int matrix1[N][N],int size1)
{/*this function gets a matrix and a requested size, and puts the input
    values in the cells.*/
    int input;
    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<size1;j++)
        {
            scanf("%d",&input);
            matrix1[i][j]=input;
        }
    }
}

int sbox[256] = { 99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254,
		215, 171, 118, 202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175,
		156, 164, 114, 192, 183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229,
		241, 113, 216, 49, 21, 4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128,
		226, 235, 39, 178, 117, 9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214,
		179, 41, 227, 47, 132, 83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190,
		57, 74, 76, 88, 207, 208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2,
		127, 80, 60, 159, 168, 81, 163, 64, 143, 146, 157, 56, 245, 188, 182,
		218, 33, 16, 255, 243, 210, 205, 12, 19, 236, 95, 151, 68, 23, 196, 167,
		126, 61, 100, 93, 25, 115, 96, 129, 79, 220, 34, 42, 144, 136, 70, 238,
		184, 20, 222, 94, 11, 219, 224, 50, 58, 10, 73, 6, 36, 92, 194, 211,
		172, 98, 145, 149, 228, 121, 231, 200, 55, 109, 141, 213, 78, 169, 108,
		86, 244, 234, 101, 122, 174, 8, 186, 120, 37, 46, 28, 166, 180, 198,
		232, 221, 116, 31, 75, 189, 139, 138, 112, 62, 181, 102, 72, 3, 246, 14,
		97, 53, 87, 185, 134, 193, 29, 158, 225, 248, 152, 17, 105, 217, 142,
		148, 155, 30, 135, 233, 206, 85, 40, 223, 140, 161, 137, 13, 191, 230,
		66, 104, 65, 153, 45, 15, 176, 84, 187, 22 };

void byte_subs(int matrix1[N][N],int size1)
{/*this function gets a matrix and it's size and uses
    "byte substitution" algorithm to encrypt the matrix.*/
    int value;
    for(int i=0;i<size1;i++)
    {
       for(int j=0;j<size1;j++)
        {
            value = matrix1[i][j];
            matrix1[i][j]=sbox[value];
        }
    }
}

void shift_rows(int matrix1[N][N],int size1)
{/*this function gets a matrix and it's size and uses
    "shift rows" algorithm to encrypt the matrix.*/
    int first;
    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<i;j++)
        {
            first=matrix1[i][0];
            for(int k=1;k<size1;k++)
            {/*starting from index 1, place the value of each cell,
             in the cell that is located on his left.*/
                matrix1[i][k-1] = matrix1[i][k];
            }
            matrix1[i][size1-1] = first;
        }/*placing the value of the first cell of the row,
         in the last cell of the row.*/
    }
}

int main()
{
    int iter,size;
    int matrix[N][N];
    print_welcome_message1();
    scanf("%d",&iter);
    while(iter<0)
    {
        print_invalid_amount();
        scanf("%d",&iter);
    }
    print_welcome_message2();
    scanf("%d",&size);
    print_enter_matrix();
    build_matrix(matrix,size);
    for(int i=0;i<iter;i++)
    {//running the encryption in iterations in order to iter's value.
        byte_subs(matrix,size);
        shift_rows(matrix,size);
    }
    print_encrypted_message();
    print_matrix(size,matrix);
  return 0;
}
