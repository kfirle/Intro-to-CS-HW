#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define EPS (1e-6)
#define N (100)
#define M (100)
#define SUCCESS (0)
#define ERROR (1)


void print(double a[][M], int n, int m);

double zero_by_threshold(double num, double eps) {
    return fabs(num) > eps ? num : 0;
}

bool read_sizes(int * n, int * m) {
    if (scanf("%d%d", n, m) != 2) {
        return false;
    }

    return ((*n >= 1) && (*n <= N) && (*m >= 1) && (*m <= M));
}

void print_matrix(double a[][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%.2f ", zero_by_threshold(a[i][j], EPS));
        }

        printf("\n");
    }

    printf("\n");
}

bool read_matrix(double a[][M], int n, int m)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(scanf("%lf",&a[i][j])!=1)
            {
                return false;
            }
        }
    }
    return true;
}

void swap_rows(double a[][M], int m, int row1, int row2)
{
    double temp;
    for(int i=0;i<m;i++)
    {
        temp=a[row1][i];
        a[row1][i] = a[row2][i];
        a[row2][i] = temp;
    }
}

void multiply_row(double a[][M], int m, int row, double scalar)
{
    for(int i=0;i<m;i++)
    {
        a[row][i] = a[row][i]*scalar;
    }
}

void add_row_to_row(double a[][M], int m, int row1, int row2, double scalar)
{
    for(int i=0;i<m;i++)
    {
        a[row1][i] = a[row1][i]+ a[row2][i]*scalar;
    }
}

bool find_leading_element(double a[][M], int n, int m, int * row, int * column)
{
    for(int j=*column;j<m;j++)
    {
        for(int i=0;i<n;i++)
        {
            if(a[i][j]!=0)
            {
                *row = i;
                *column = j;
                return true;
            }
        }
    }
    return false;
}

void reduce_rows(double a[][M], int n, int m)
{
    int row=0,column=0;
    double scalar;
    for(int i=0;i<n;i++)
    {
        if(find_leading_element(a+i,n-i,m,&row,&column)==false)
        {
            break;
        }
        if(row!=0)
        {
            swap_rows(a,m,row+i,i);
        }
        row=i;
        if(a[row][column]!=1)
        {
            multiply_row(a,m,row,1/a[row][column]);
        }
        for(int t=i+1;t<n;t++)
        {
            if(a[t][column]!=0)
            {
                scalar = (-1) * a[t][column] / a[row][column];
                add_row_to_row(a,m,t,i,scalar);
            }
        }
        column++;
    }
}

int main()
{
    int n;
    int m;
    printf("Enter matrix size (row and column numbers): ");
    if (!read_sizes(&n, &m)) {
        printf("Invalid sizes!\n");
        return ERROR;
    }

    double a[N][M];
    printf("Enter matrix:\n");
    if (!read_matrix((double (*)[M]) a, n, m)) {
        printf("Invalid matrix!\n");
        return ERROR;
    }

    reduce_rows((double (*)[M]) a, n, m);
    printf("The reduced matrix:\n");
    print_matrix((double (*)[M]) a, n, m);
    return SUCCESS;
}
