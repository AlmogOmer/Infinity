#include <stdio.h>
#include<string.h>
#include<stdlib.h>
typedef enum {INT, FLOAT, CHAR} types;
typedef struct elements 
{
	types type;
	int num;
	float flot;
	char str[50];
	
} elements;

void print(elements *el);
void add(elements *el, int addnum);
void cleanup(elements *arr);
int main()
{
	int addnum = 10;
	size_t i = 0;
	size_t size = 3;
	elements *arr = (elements *)malloc(size*sizeof(elements));
	if (arr == NULL)
		return 1;
		
	arr[0].type = INT;
	arr[0].num = 12;
	arr[1].type = FLOAT;
	arr[1].flot = 4.2;
	arr[2].type = CHAR;
	strcpy(arr[2].str,"chapter");
	for (i = 0; i < size; ++i)
	{
		add(&arr[i], addnum);
		print(&arr[i]);
	}
	cleanup(arr);	
	return 0;
}

void print(elements *el)
{
	switch (el->type)
	{
		case INT:
			printf("%d\n",el->num);
			break;
		case FLOAT:
			printf("%.6f\n", el->flot);
			break;
		case CHAR:
			printf("%s\n", el->str);
			break;			
	}
}


void add (elements *el, int addnum)
{
	char addstr[50];
	switch (el->type)
	{
		case INT:
			el->num += addnum;
			break;
		case FLOAT:
			el->flot += (float)addnum;
			break;
		case CHAR:
			sprintf(addstr,"%d",addnum);
			strcat(el->str, addstr);
			break;
				
	}	
	
}


void cleanup(elements *arr)
{
	
	free(arr);	
	arr = NULL;
}





