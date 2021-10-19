#include <stdio.h>
#include <stdlib.h>
void input_if ();
int main ()
{
	input_if();
	return 0;
}

void input_if ()
{
	char input;
	while (1)
	{
		scanf("%c", &input);
		if ('A' == input)
		{
			printf("A-pressed");
		}
		else if ('T' == input)
		{
			printf("T-pressed");
		}
		else if (27 == input)
		{
			exit (0);
		}
	}
}

			
		
