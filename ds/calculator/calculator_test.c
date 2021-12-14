#include "calculator.h"
#include "stack.h"
#include <assert.h>		
#include <stdio.h>

static void Test(void);

int main(void)
{
    Test();

    return 0;
}

static void Test(void)
{

    assert(8 == Calculator("3 +5"));
    
    
    assert(28 == Calculator("3+5+1+8+6+5"));
    
    
    assert(35 == Calculator("20+15"));
   
    
    assert(15 == Calculator("3*5"));
    

    assert(-20 == Calculator("7+68-95"));
    
    assert(31 == Calculator("3+5*4+8"));

    assert(96 == Calculator("(3+5)*(4 + 8)"));
   
    assert(96 == Calculator("(((3)+5) * ((4 + 8)))"));
   
    printf("SUCCESS");
}



