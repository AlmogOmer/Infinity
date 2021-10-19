#include <stdio.h>
#include <stdlib.h>
void input_switch ();
int main ()
{
	input_switch();
	return 0;
}

void input_switch ()
{
	char input;
	while (1)
	{
		scanf("%c", &input);
		switch (input)
		{
			case 'A' :
			printf("A-pressed");
			break;
			case 'T' :
			printf("T-pressed");
			break;
			case 27 :
			exit (0);
			break;
		}
	}
}

