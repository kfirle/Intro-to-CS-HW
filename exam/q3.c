
/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#define ABC 26
#define ENG 'a'


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
int length_of_longest_stunning_substr(char* str)
{
    int letters[ABC]={0};
    int length=0,i=0,left=0;
    while(str[i]!='\0')
    {
        int valid =1;
        int index = (int) (str[i]-ENG);
        letters[index]++;
        for(int j=0;j<ABC;j++)
        {
            if(letters[j]>1)
            {
                valid=0;
                int index2 = (int)(str[left]-ENG);
                letters[index2]--;
                left++;
                break;
            }
        }
        length += valid;
        i++;
    }
    return length;
}


/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{

  return 0;
}
