/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define N 4
#define NO_ROAD -1
#define NO_PATH -1

int ShortestFullPath(int roads[N][N]);
bool visited_all_houses(int houses[N]);
bool valid_roads_left(int roads[N][N],int current);
void find_path(int roads[N][N],int houses[N],int current, int length,
                int* shortest);

// Print functions declarations
void PrintRoadsInputMessage();
void PrintLenOfShortestFullPath(int min_len);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int min_path,num;
    int roads[N][N];
    PrintRoadsInputMessage();
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            scanf("%d",&num);
            roads[i][j]=num;
        }
    }
    min_path = ShortestFullPath(roads);
    PrintLenOfShortestFullPath(min_path);
    return 0;
}

bool visited_all_houses(int houses[N])
{
    for(int i=0;i<N;i++)
    {
        if(houses[i]==0)
        {
            return false;
        }
    }
    return true;
}

bool valid_roads_left(int roads[N][N],int current)
{
    for(int i=0;i<N;i++)
    {
        if(roads[current][i]>0)
        {
            return true;
        }
    }
    return false;
}

void find_path(int roads[N][N],int houses[N],int current, int length,
                int* shortest)
{
    if(valid_roads_left(roads,current)==false)
    {
        return;
    }
    if(visited_all_houses(houses)==true)
    {
        if(current == 0)
        {
            if(*shortest == NO_PATH)
            {
                *shortest = length;
            }
            else
            {
                if(length < *shortest)
                {
                    *shortest = length;
                }
            }
        }
        return;
    }
    if(!(current ==0 && houses[0]==1))
    {
        for(int i=0;i<N;i++)
        {
            if(roads[current][i] > 0 && houses[i]==0)
            {
                houses[i]=1;
                length+=roads[current][i];
                find_path(roads,houses,i,length,shortest);
                length-=roads[current][i];
                houses[i]=0;
            }
        }
    }
}

int ShortestFullPath(int roads[N][N])
{
    int houses[N]={0,0,0,0};
    int min_length=NO_PATH, length = 0,current = 0;
    find_path(roads,houses,current, length, &min_length);
    return min_length;

}

// Print functions
void PrintLenOfShortestFullPath(int min_len)
{
    if(min_len == NO_PATH)
    {
        printf("There is no such path!\n");
    }
    else
    {
        printf("The shortest path is of length: %d\n", min_len);
    }
}

void PrintRoadsInputMessage()
{
    printf("Please enter the roads %dX%d matrix row by row:\n", N, N);
}
