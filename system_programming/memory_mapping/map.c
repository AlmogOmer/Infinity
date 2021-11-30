#include <stdio.h>
#include <stdlib.h>

static void s_fun(void);
extern void ex_fun(void);

const int cg = 6; 
static const int sc = 8;
int g = 7;
static int s = 1;

int main()
{
    int *p = (int *)malloc(sizeof(int));
    const int c = 5;
    int x = 2;
    static int s = 4;
    static const int scl = 9;
    char *str = "hello";

    s_fun();
    ex_fun();


    return 0;


}

static void s_fun(void)
{
    printf("im s_fun\n");
}
extern void ex_fun(void)
{
     printf("im ex_fun\n");

}
