#include <stdio.h>
#include<assert.h>
#include <string.h>
#include "recursion.h"
#include "stack_rec.h"

static void Fibonacci_test();
static void FlipList_test();
static void Strlen_test();
static void Srtcmp_test();
static void Strcpy_test();
/*static void Strcat_test();*/
static void Strstr_test();
static void stack_sort_test();

int main()
{

    Fibonacci_test();
    FlipList_test();
    Strlen_test();
    Srtcmp_test();
    Strcpy_test();
    /*Strcat_test();*/
    Strstr_test();
    stack_sort_test();

    return 0;
}

static void Fibonacci_test()
{
    int index = 5;
    int index2 = 2;
    int index3 = 6;
    assert(3 == Fibonacci(index));
    assert(1 == Fibonacci(index2));
    assert(5 == Fibonacci(index3));

    puts("success Fibonacci test\n");
}

static void FlipList_test()
{
    int i;
    node_t list[20];
    node_t *result;

    for(i=0; i<19; ++i)
    {
        list[i].data = i;
        list[i].next = &list[i+1];
    }

    list[i].data = i;
    list[i].next = NULL;

    result = FlipList(list);

    for(i=0; i<19; ++i)
    {
        assert(&list[i] == list[i+1].next);
        
    }
    
    assert(list[0].next == NULL);


    puts("success FlipList test\n");
}


static void Strlen_test()
{
    char *str1 = "almog";
    char *str2 = "12345678";

    assert(5 == Strlen_recu(str1));
    assert(8 == Strlen_recu(str2));

    puts("success Strlen test\n");
}


static void Srtcmp_test()
{
    char *str1 = "almog";
    char *str2 = "12345678";

    char *str3 = "aaa";
    char *str4 = "aaa";

    assert(0 != Srtcmp_recu(str1, str2));
    assert(0 == Srtcmp_recu(str3, str4));

    puts("success Srtcmp test\n");
}

    
static void Strcpy_test()
{    
    char dest[10] = {0};
    char *src = "hello";
	
    Strcpy_recu(dest, src);
    assert(0 == strcmp(dest,src));

    puts("success Strcpy test\n");
}


/*static void Strcat_test()
{    
    char *dest = "bbb";
    char *src = "hello";
	
    
    printf("dest is: %s\n", Strcat_recu(dest, src));

    puts("success Strcat test\n");
}*/

static void Strstr_test()
{    
    char *haystack = "llhello";
    char *needle = "llo";
	
    assert(0 == strcmp(Strstr_recu(haystack, needle), "llo"));

    puts("success StrStr test\n");
}

static void stack_sort_test()
{
    struct Stack *stack = NULL;
    stack = createStack(7);
    push(stack, 5);
    push(stack, 1);
    push(stack, 6);
    push(stack, 3);
    push(stack, 2);
    push(stack, 7);
    push(stack, 4);

    printf("Unsorted Stack:\n");
    Print(stack);
    Sort_stack(stack);

    printf("Sorted Stack:\n");
    Print(stack);

}



