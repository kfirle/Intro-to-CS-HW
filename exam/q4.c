/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 3


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/

void read_numbers(int grid [N*N][N*N])
{
    int num;
    printf("Insert Numbers\n");
    for(int i=0;i<N*N;i++)
    {
        for(int j=0;j<N*N;j++)
        {
            scanf("%d",&num);
            grid[i][j] = num;
        }
    }
    printf("\n");
}
void print_grid(int grid [N*N][N*N])
{
    for(int i=0;i<N*N;i++)
    {
        for(int j=0;j<N*N;j++)
        {
            int num = grid[i][j];
            printf("%d ",num);
        }
        printf("\n");
    }
    printf("\n");
}

bool is_in_col(int grid [N*N][N*N],int num, int col)
{
    for(int i=0;i<N*N;i++)
    {
        if(grid[i][col]==num)
        {
            return true;
        }
    }
    return false;
}

bool is_in_row(int grid [N*N][N*N],int num, int row)
{
    for(int i=0;i<N*N;i++)
    {
        if(grid[row][i]==num)
        {
            return true;
        }
    }
    return false;
}

bool is_in_sqr(int grid [N*N][N*N],int num,int col, int row)
{
    int up=N*(row/N);
    int down = N*(row/N)+N;
    int right = N*(col/N)+N;
    int left = N*(col/N);
    for(int i=up;i<down;i++)
    {
        for(int j=left;j<right;j++)
        {
            if(grid[i][j]==num)
            {
                return true;
            }
        }
    }
    return false;
}
bool is_valid(int grid[N*N][N*N],int num,int col,int row)
{
    if(is_in_col(grid,num,col)==true)
    {
        return false;
    }
    if(is_in_row(grid,num,row)==true)
    {
        return false;
    }
    if(is_in_sqr(grid,num,col,row)==true)
    {
        return false;
    }
    return true;
}
void func(int grid [N*N][N*N],int row,int col,int* count)
{
    if(row>N*N-1 && col == N*N)
    {
        print_grid(grid);
        (*count)++;
        return;
    }
    if(col == N*N)
    {
        func(grid,row+1,0,count);
        return;
    }
    if(grid[row][col]!=0)
    {
        func(grid,row,col+1,count);
        return;
    }
    for(int i=1;i<=N*N;i++)
    {
        if(is_valid(grid,i,col,row)==false)
        {
            continue;
        }
        grid[row][col]=i;
        func(grid,row,col+1,count);
        grid[row][col]=0;
    }
    return;
}
int count_sol(int grid[N*N][N*N])
{
    int count=0;
    func(grid,0,0,&count);
    return count;
}

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int grid [N*N][N*N];
    read_numbers(grid);
    int count = count_sol(grid);
    printf("The number of solutions: %d\n",count);
  return 0;
}
