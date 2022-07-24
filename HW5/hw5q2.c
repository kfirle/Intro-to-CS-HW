/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define LEX 1
#define LET_DIVER 2
#define MAX_LEN 20
#define EQUAL 0
#define HIGHER 1
#define LOWER -1
#define NUM_OF_LETTERS 26

int CompareStrings(char* str1, char* str2, int rule);
void SortStrings(char* str_arr[], int n, int rule);
bool read_strings(char* strings[],int num);
int ascii_letters_compare(char letter1, char letter2);
void check_diversity(int div[],char* str);

// Print Functions' Declarations
void PrintNumStringsInputMessage();
void PrintStringsInputMessage(int n);
void PrintRuleOfComparisonInputMessage();
void PrintSortedStrings(char* str_arr[], int n);
void PrintAllocationError();

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int num,rule;
    PrintNumStringsInputMessage();
    scanf("%d",&num);
    PrintStringsInputMessage(num);
    char** strings = (char**)(malloc(sizeof(char*)*num));
    if(strings==0)
    {
        PrintAllocationError();
    }
    else
    {
        if(read_strings(strings,num)==false)
        {
            PrintAllocationError();
        }
        else
        {
            PrintRuleOfComparisonInputMessage();
            scanf("%d",&rule);
            SortStrings(strings,num,rule);
            PrintSortedStrings(strings,num);
        }
    }
    return 0;
}

bool read_strings(char* strings[],int num)
{
    for(int i=0;i<num;i++)
    {
        char word[MAX_LEN+1];
        if(scanf("%s",word)!=1)
        {
            return false;
        }
        int length = strlen(word)+1;
        char* address = (char*)(malloc(sizeof(char)*length));
        if(address == 0)
        {
            return false;
        }
        for(int j=0;j<length;j++)
        {
            address[j] = word[j];
        }
        strings[i] = address;
    }
    return true;
}

void check_diversity(int div[],char* str)
{
    int i=0;
    char letter=str[0];
    while(letter!='\0')
    {
        if(letter >='a' && letter <='z')
        {
            letter = letter -'a'+'A';
        }
        if(letter >='A' && letter <='Z')
        {
            div[letter -'A']++;
        }
        i++;
        letter=str[i];
    }
}

int CompareStrings(char* str1, char* str2, int rule)
{
    if(rule==LEX)
    {
        int status;
        for(int i=0;i<MAX_LEN+1;i++)
        {
            if(str1[i]=='\0' && str2[i]=='\0')
            {
                return EQUAL;
            }
            status = ascii_letters_compare(str1[i],str2[i]);
            if(status!=EQUAL)
            {
                return status;
            }
        }
    }
    else
    {
        int div1[NUM_OF_LETTERS]={0},div2[NUM_OF_LETTERS]={0};
        int count1=0,count2=0;
        check_diversity(div1,str1);
        check_diversity(div2,str2);
        for(int j=0;j<NUM_OF_LETTERS;j++)
        {
            if(div1[j] > 0)
            {
                count1++;
            }
            if(div2[j] > 0)
            {
                count2++;
            }
        }
        if(count1==count2)
        {
            return EQUAL;
        }
        if(count1 > count2)
        {
            return HIGHER;
        }
    }
    return LOWER;
}

int ascii_letters_compare(char letter1, char letter2)
{
    if(letter1 >='a' && letter1 <='z')
    {
        letter1 = letter1 -'a'+'A';
    }
    if(letter2 >='a' && letter2 <='z')
    {
        letter2 = letter2 -'a'+'A';
    }
    if(letter1 == letter2)
    {
        return EQUAL;
    }
    if(letter1 > letter2)
    {
        return HIGHER;
    }
    else
    {
        return LOWER;
    }
}

void SortStrings(char* str_arr[], int n, int rule)
{
    char* temp;
    for(int i=0;i<n-1;i++)
    {
        bool sorted=true;
        for(int j=0;j<n-i-1;j++)
        {
            if(CompareStrings(str_arr[j],str_arr[j+1],rule)==HIGHER)
            {
                sorted=false;
                temp = str_arr[j];
                str_arr[j] = str_arr[j+1];
                str_arr[j+1] = temp;
            }
        }
        if(sorted==true)
        {
            return;
        }
    }
}

// Print Functions
void PrintNumStringsInputMessage()
{
    printf("Please enter the number of strings:\n");
}

void PrintStringsInputMessage(int n)
{
    printf("Please enter the %d strings:\n", n);
}

void PrintRuleOfComparisonInputMessage()
{
    printf("Please enter the rule of comparison between strings.\n");
    printf("%d: Lexicographic order.\n", LEX);
    printf("%d: By the diversity of letters.\n", LET_DIVER);
}

void PrintSortedStrings(char* str_arr[], int n)
{
    printf("The sorted strings are:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%s\n", str_arr[i]);
    }
}

void PrintAllocationError()
{
    printf("ERROR: allocation failed.\n");
}
