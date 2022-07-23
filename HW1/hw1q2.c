#include <stdio.h>
int main()
{
    int shift=0,round=0;
    char text;
    printf("Please enter shift number:\n");
    scanf("%d",&shift);
    shift = shift % 26; //because there are 26 letters in English
    printf("Please enter text to encrypt:\n");
    while(scanf("%c",&text)!=EOF) //reading the user's text until the end of the file or Ctrl+z
    {
        if((text >= 'a' && text <='z') || (text >= 'A' && text <='Z'))
        {
            if(text >= 'a' && text <='z')
            {
                round = text + shift - 'z'; //counting the gap between the letter and z
                if(round>0){text = 'a' + (round-1);} //if we have passed z, we need to go back to a
                else{text = text + shift;}
                printf("%c",text);
            }
            else
            {
                round = text + shift - 'Z'; //counting the gap between the letter and Z
                if(round>0){text = 'A' + (round-1);} //if we have passed Z, we need to go back to A
                else{text = text + shift;}
                printf("%c",text);
            }
        }
        else
        {
            if(text == '\n'){printf("\n");}
            else{printf("%c",text);}
        }
    }
    printf("\n");
  return 0;
}
