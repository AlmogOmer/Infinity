#include "big_num.h"
#include<string.h>
#include<stdio.h>


int main()
{
    intbig_t b1,b2, result;
    char *str1 = "532";
    char *str2 = "555";

    b1 = StrToBig(str1);
    b2 = StrToBig(str2);

    result = BigAdd(b1, b1);
    printf("%x\n", result);
    printf("%x\n", 532+555);
    return 1;
}




