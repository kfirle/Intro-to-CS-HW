/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/

int meeting_point(int a[],int na,int b[],int nb)
{
    int left=0,right,min=-1;
    if(na>nb)
    {
        right=nb-1;
    }
    else
    {
        right=na-1;
    }
    while(left<=right)
    {
        if(a[left]==b[left])
        {
            return left;
        }
        int mid=(left+right)/2;
        if(a[mid]>b[mid])
        {
            left=mid+1;
        }
        else
        {
            if(a[mid]<b[mid])
            {
                right=mid-1;
            }
            else
            {
                if(min==-1)
                {
                    min=mid;
                }
                else
                {
                    if(mid<min)
                    {
                        min=mid;
                    }
                }
                right=mid-1;
            }
        }
    }
    return min;
}

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int a[9] = {19,19,16,15,15,15,15,13,-2};
    int b[10]={0,12,13,14,14,15,15,19,42,57};
    int index = meeting_point(a,3,b,8);
    printf("Index: %d\n",index);
  return 0;
}
