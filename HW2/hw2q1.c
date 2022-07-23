#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int print_welcome_message(){
    return printf("La Inspectora Murillo, Please enter El Professor name:\n");
}

int print_Walter_White_sent(){
    return printf("\nEl Professor sent Walter White into the robbery!\n");
}

int print_Daenerys_sent(){
    return printf("\nEl Professor sent Daenerys Targaryen into the robbery!\n");
}

int print_Doron_Kabilio_sent(){
    return printf("\nEl Professor sent Doron Kabilio into the robbery!\n");
}

int print_no_player(){
    return printf("\nNO player has been sent into the robbery!\n");
}

int check(int count1, int r_flag1, int ascend1,int sum1)
{/* this function finds who will join the robbery and calls
     the relevant printing function.
    count1 - number of letters of the prof's name.
    r_flag1 - marks whether 'r' was typed.
    ascend1 - marks whether the name is an
     ascending arithmetic progression.
    sum1 = sum of ASCII values */
    if(ascend1==1)
    {
        print_Daenerys_sent();
        return 0;
    }
    if((count1<6) && (r_flag1!=1))
    {
        print_Doron_Kabilio_sent();
        return 0;
    }
    if((sum1%5 != 0) || (count1 > 4))
    {
        print_Walter_White_sent();
        return 0;
    }
    print_no_player();
    return 0;
}
int main()
{
    int count=0,r_flag=0,ascend=1,sum=0;
    char previous='a'-1,letter;
    print_welcome_message();
    scanf("%c" ,&letter);
    while(letter != '!')
    {
        ascend = (ascend && (letter > previous));
        //ascending arithmetic progression flag.
        sum+=letter;//sum of ASCII values.
        if(letter == 'r')
        {//if 'r' was typed.
            r_flag = 1;
        }
        count++;
        previous=letter; /*saving the current letter for
        comparison with the following letter*/
        scanf("%c" ,&letter);
    }
    check(count,r_flag,ascend,sum);
	return 0;
}
