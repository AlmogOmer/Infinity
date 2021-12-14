#include "calculator.h"
#include "stack.h"
#include <assert.h>		
#include <stdio.h>

static void Test(void);
static void test2();

int main(void)
{
    Test();
    test2();
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

    assert(55 == Calculator("30*2- (10+20) / 6"));
    
    assert(-10 == Calculator("5*-2"));

    assert(-40 == Calculator("-5*2 +3*-10"));
    
    printf("SUCCESS\n");
}

static void test2()
{
    assert(!(int)(Calculator("20.30300 + 48.694 - 17 * 25.34 + 4 / 2 + 0") + 359.783000));
	assert(Calculator("2+3 * 16.5 +22 * (15.5*16.2) +1") == 5576.70);
	assert(!(int)(Calculator("-7+14") - 7));
	
	/* testing unary and binary states */
    assert(Calculator("1") == 1);
    assert(Calculator("+1") == 1);
    assert(Calculator("-1") == -1);
    assert(Calculator("-1 + 1") == 0);
    assert(Calculator("-1 - 1") == -2);
    assert(Calculator("-1 - -1") == 0);
    assert(Calculator("1 - -1") == 2);
    assert(Calculator("+1 - 1") == 0);
    assert(Calculator("-1 * (-1 + 2)") == -1 );
    assert(Calculator("-1 * (-1 - 2)") == 3);

    printf("SUCCESS2\n");


}



