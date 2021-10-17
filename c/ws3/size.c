#include <stdio.h>
#include <assert.h>
#include <stddef.h>

int main()
{
	size_t ch = sizeof(char);
	size_t in = sizeof(int);
	size_t ui = sizeof(unsigned int);
	size_t lg = sizeof(long);
	size_t ul = sizeof(unsigned long);
	size_t ft = sizeof(float);
	size_t db = sizeof(double);
	size_t ld = sizeof(long double);
	printf("char: %ld\nint: %ld\nunsigned int: %ld\nlong: %ld\nunsigned long: %ld\nfloat: %ld\ndouble: %ld\nlong double: %ld\n",ch,in, ui,lg,ul,ft,db,ld); 
	fflush(stdout);
	
	return 0;
}


