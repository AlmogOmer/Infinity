#include <stdio.h>
#include <stdlib.h>
typedef void (*func)();
void A_pressed();
void T_pressed();
void Esc();
void NULLchar();
void input_LUT ();
func LUT_ARRAY[128] = {NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, Esc, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, A_pressed, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, T_pressed, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar, NULLchar};
void create_LUT();
void input_LUT ();
int main ()
{
	input_LUT();
	return 0;
}

void input_LUT ()
{
	char input;
	while (1)
	{
		scanf("%c", &input);
		LUT_ARRAY[(int)input]();
	}
}
void A_pressed()
{
	printf("A_pressed");
}

void T_pressed()
{
	printf("T_pressed");
}

void Esc()
{
	exit(0);
}

void NULLchar()
{
	NULL;
}

void create_LUT()
{
	int i;
	printf("[");
	for ( i = 0; i<128 ; ++i)
	{
		if (65 == i)
		{
			printf("A_pressed, ");
		}
		else if (84 == i)
		{
			printf("T_pressed, ");
		}
		else if (27 == i)
		{
			printf("Esc, ");
		}
		else
		{
			printf("NULLchar, ");
		}
	}
	printf("]");
}










		

