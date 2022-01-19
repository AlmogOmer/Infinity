#ifndef __BIG_NUM_H__
#define __BIG_NUM_H__

#include <stddef.h>

typedef struct Big
{
    unsigned int LSW;
    int MSW;
} intbig_t;

extern intbig_t BigAdd(intbig_t a, intbig_t b);

extern intbig_t BigSub(intbig_t a, intbig_t b);

extern intbig_t BigMul(intbig_t a, intbig_t b);

extern intbig_t BigDiv(intbig_t a, intbig_t b);

extern intbig_t BigShiftL(intbig_t a, unsigned char shift);

extern intbig_t StrToBig(char *str);

#endif



