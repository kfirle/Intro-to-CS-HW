#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N (100)
#define MAX_LEN (255)
#define MAX_SENTENCE_LEN ((MAX_LEN + 1) * N - 1)
#define WORD_SEPERATOR ('_')
#define SUCCESS (0)
#define ERROR (1)
#define EQUAL 0
#define HIGHER 1
#define LOWER -1

bool read_number_of_strings(int * n) {
    if (scanf("%d", n) != 1) {
        return false;
    }

    return ((*n >= 1) && (*n <= N));
}

void free_strings(char * strings[], int n)
{
    for(int i=0;i<n;i++)
    {
        free(strings[i]);
    }
}

bool read_strings(char * strings[], int n)
{
    for(int i=0;i<n;i++)
    {
        char word [MAX_LEN+1];
        if(scanf("%s", word)!= 1)
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

int letters_compare(char letter1, char letter2)
{
    if((letter1>= 'A' && letter1 <='Z')&&(letter2 >='a' &&letter2 <='z'))
    {
        if(letter1 +'a'-'A' == letter2)
        {
            return EQUAL;
        }
        if(letter1 +'a'-'A' > letter2)
        {
            return HIGHER;
        }
        else
        {
            return LOWER;
        }
    }
    if((letter2>= 'A' && letter2 <='Z')&&(letter1 >='a' &&letter1 <='z'))
    {
        if(letter2 +'a'-'A' == letter1)
        {
            return EQUAL;
        }
        if(letter2 +'a'-'A' > letter1)
        {
            return LOWER;
        }
        else
        {
            return HIGHER;
        }
    }
    else
    {
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
}

bool are_sorted(char * strings[], int n)
{
    for(int i=0;i<n-1;i++)
    {
        int count=0,diff;
        char* word1 = strings[i];
        char* word2 = strings[i+1];
        char letter1 = *(word1+count);
        char letter2 = *(word2+count);
        while(letter1 !='\0' && letter2!='\0')
        {
            diff = letters_compare(letter1,letter2);
            if(diff == HIGHER)
            {
                return false;
            }
            if(diff == LOWER)
            {
                break;
            }
            count++;
            letter1 = *(word1+count);
            letter2 = *(word2+count);
        }
        if(letter1 !='\0' && letter2=='\0')
        {
            return false;
        }
    }
    return true;
}

bool is_string_in_array(char * strings[], int n, char * string)
{
    int count=0, left=0, right=n-1,mid=n/2,diff;
    while(right>=0 && left <n && right>=left)
    {
        char* word = strings[mid];
        char letter = *(word+count);
        char str_letter = *(string+count);
        while(str_letter !='\0' || letter!='\0')
        {
            letter = *(word+count);
            str_letter = *(string+count);
            diff = letters_compare(str_letter,letter);
            if(diff==EQUAL)
            {
                count++;
            }
            else
            {
                if(diff ==HIGHER)
                {
                    left = mid+1;
                    mid = (right+left)/2;
                    count=0;
                    break;
                }
                else
                {
                    right = mid-1;
                    mid = (right+left)/2;
                    count=0;
                    break;
                }
            }
        }
        if(str_letter =='\0' && letter=='\0')
        {
            return true;
        }
    }
    return false;
}

void delete_words(char * words[], int n, char * sentence)
{
    int count2=0;
    int length = strlen(sentence);
    char new_sentence[MAX_SENTENCE_LEN+1];
    while(count2<length)
    {
        char* word = (char*)(malloc(sizeof(char)*MAX_LEN+1));
        int count=0;
        for(int i=0;i<MAX_LEN+1;i++)
        {
            word[i] = '\0';
        }
        while((sentence[count2]!=WORD_SEPERATOR)&&(sentence[count2]!='\0'))
        {
            *(word+count) = sentence[count2];
            count++;
            count2++;
        }
        if(is_string_in_array(words,n,word)==false)
        {
            *(word+count) = sentence[count2];
            strcat(new_sentence,word);
        }
        if(sentence[count2]==WORD_SEPERATOR)
        {
            count2++;
        }
        free(word);
    }
    int new_length = strlen(new_sentence);
    if((sentence[length-1]!=WORD_SEPERATOR)&&(new_sentence[new_length-1]
                                              ==WORD_SEPERATOR))
    {
        new_sentence[new_length-1] = '\0';
    }
    strcpy(sentence,new_sentence);
}

int main() {
    int n;
    printf("Enter number of banned words: ");
    if (!read_number_of_strings(&n)) {
        printf("Invalid number!\n");
        return ERROR;
    }

    char * banned_words[N];
    printf("Enter banned words: ");
    if (!read_strings(banned_words, n)) {
        printf("Can't read words!\n");
        return ERROR;
    }

    if (!are_sorted(banned_words, n)) {
        printf("Words are not sorted correctly!\n");
        free_strings(banned_words, n);
        return ERROR;
    }

    char sentence[MAX_SENTENCE_LEN + 1];
    printf("Enter a sentence:\n");
    if (scanf("%s", sentence) != 1) {
        printf("Invalid sentence!\n");
        free_strings(banned_words, n);
        return ERROR;
    }

    delete_words(banned_words, n, sentence);
    printf("Censored sentence:\n%s\n", sentence);
    free_strings(banned_words, n);
    return SUCCESS;
}
