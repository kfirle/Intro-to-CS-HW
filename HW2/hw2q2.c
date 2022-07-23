#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_welcome_message(){
	printf("Please enter a character:\n");
}

void print_welcome_message2(){
	printf("Please enter votes:\n");
}

void print_introduce_histogram(){
	printf("Histogram:\n");
}

void print_TA(int ta){
	switch (ta) {
		case 1:
			printf("Adi was elected!\n");
			break;
		case 2:
			printf("Alon was elected!\n");
			break;
		case 3:
			printf("Assaf was elected!\n");
			break;
		case 4:
			printf("Daniella was elected!\n");
			break;
		case 5:
			printf("Danielle was elected!\n");
			break;
		case 6:
			printf("Dmitry was elected!\n");
			break;
		case 7:
			printf("Gasob was elected!\n");
			break;
		case 8:
			printf("Ido was elected!\n");
			break;
		case 9:
			printf("Najeeb was elected!\n");
			break;
		case 10:
			printf("Nir was elected!\n");
			break;
		case 11:
			printf("Omer was elected!\n");
			break;
		case 12:
			printf("Yair was elected!\n");
			break;
		case 13:
			printf("Yara was elected!\n");
			break;
	}
}

int find_the_winner(int results1[])
{/* this function gets the results array and finds who got
    the biggest amount of votes.*/
    int max=0,index=0,i;
    for(i=1; i<14; i++)
    {
        if(results1[i]>max)
        {
            max = results1[i];
            index = i;
        }
    }
    return index;
}

void print_histogram(int results1[],char sign1,int index1)
{/* this function gets the results array, and prints the histogram.
    results1 - the results array.
    sign1 - the char that was selected for the printing.
    index1 - the index of the winner.*/
    int i,j,max1=0;
    max1 = results1[index1];
    for(i=max1; i>0; i--)
    {//counting backwards in order to print the results.
        for(j=1; j<14; j++)
        {/*for every cell in the array, print sign1 if the number of
            votes that the contestant got is equal or bigger than the
            value of i in the current iteration.
            otherwise, print space if the index of the cell is a digit
            or double scape if the number has 2 digits.*/
            if(results1[j]>=i)
            {
                if(j>=10)
                {
                    printf("%c  ",sign1);
                }
                else
                {
                    printf("%c ",sign1);
                }
            }
            else
            {
                if(j>=10)
                {
                    printf("   ");
                }
                else
                {
                    printf("  ");
                }
            }
        }
        printf("\n");
    }
    for(j=1; j<14; j++)
    {
        printf("%d ",j);
    }
    printf("\n");
    print_TA(index1);
}

int main()
{
    int vote=0,i,index;
    int results[14];
    char sign;
    for(i=1; i<14; i++)
    {//setting the array's cells to zero.
        results[i]=0;
    }
    print_welcome_message();
    scanf("%c",&sign);
    print_welcome_message2();
    while(vote!=-1)
    {
        scanf("%d",&vote);
        results[vote]++;
    }
    print_introduce_histogram();
    index = find_the_winner(results);
    print_histogram(results,sign,index);
	return 0;
}
