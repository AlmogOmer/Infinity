#include "big_num.h"
#include<string.h>
#include<stdlib.h>


/*typedef struct Big
{
    int LSW;
    int MSW;
} intbig_t;*/

/*static void reverse(char *str);*/

intbig_t BigAdd(intbig_t a, intbig_t b)
{
    intbig_t result;
    int carry = 0;
    result.LSW = a.LSW + b.LSW;
    if(result.LSW < a.LSW)
    {
        carry = 1;
    }
    result.MSW = carry + a.MSW + b.MSW;

    return result;
}

intbig_t minus(intbig_t a)
{
    intbig_t result;
    intbig_t one = {1,0};
    result.LSW = ~a.LSW;
    result.MSW = ~a.MSW;
    result = BigAdd(result, one);
}

int bigger(intbig_t a, intbig_t b)
{
    if (a.MSW > b.MSW)
    {
        return 1;
    }

    else if(a.LSW > b.LSW && a.MSW == b.MSW)
    {
        return 1;
    }

    return 0;
}

int is_equal(intbig_t a, intbig_t b)
{
    return a.LSW == b.LSW && a.MSW == b.MSW;
}


intbig_t BigSub(intbig_t a, intbig_t b)
{
    return(BigAdd(a, minus(b)));
}

intbig_t BigMul(intbig_t a, intbig_t b)
{
    intbig_t result;
    intbig_t one = {1,0};
    intbig_t zero = {0,0};
    while(bigger(b,zero))
    {
        result = BigAdd(result, BigAdd(a, a));
        BigSub(b, one);
    }
    
    return result;
}

intbig_t BigDiv(intbig_t a, intbig_t b)
{

}

intbig_t BigShiftL(intbig_t a, unsigned char shift)
{

}

intbig_t StrToBig(char *str)
{
    intbig_t result;
    intbig_t ten = {10,0};
    intbig_t digit = {0,0};
    
    while(*str)
    {
        digit.LSW = *str - '0';
        result = BigAdd(BigMul(result,ten), digit);
        ++str;
        
    }

    return result;
}

/*static void reverse(char *str)
{
    char temp;
    size_t len = strlen(str);
    size_t i = 0;
    for(i = 0; i < len/2; ++i)
    {
        temp = str[i];
        str [i] = str[len-1-i];
        str[len-1-i] = temp;
    }
}*/

