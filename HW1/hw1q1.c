#include <stdio.h>
int main()
{
    int boys_sum=0,girls_sum=0,boys_count=0,girls_count=0,height=0,err=0;
    double boys_avg=0,girls_avg=0;
    printf("Students, please enter heights!\n");
    while(scanf("%d",&height)!= EOF) //reading the heights from the user until the end of the file or Ctrl+z
    {
        if(height == 0)
        {
            printf("Error! Invalid height 0!\n");
            err=1;
            break; //update the flag 'err' if height 0 was inserted and stop getting more input
        }
        if(height>0)
        {
            girls_sum+=height;
            girls_count++;
        }
        else
        {
            boys_sum+=height;
            boys_count++;
        }
    }
    if(err !=1) //if height 0 wasn't inserted, we can calculate the avg's
    {
        if(girls_count != 0)
        {
            girls_avg = (double)(girls_sum) / girls_count;
            printf("Average girls height is: %.2f\n",girls_avg);
        }
        else{printf("No girls in class! :(\n");}
        if(boys_count != 0)
        {
            boys_count = boys_count * (-1);
            boys_avg = (double)(boys_sum) / boys_count;
            printf("Average boys height is: %.2f\n",boys_avg);
        }
        else{printf("No boys in class! :(\n");}
    }
  return 0;
}
