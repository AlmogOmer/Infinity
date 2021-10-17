#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>	
#include <string.h>	
#include <assert.h>

void PrintEnv(char **env);
char **DupEnv(char *env[]);
void ToLower(char *str);

int main(int argc, char *argv[], char *env[])
{
	char **env_dup = NULL;
	
	PrintEnv(env);	/* prints original env variables */
	
	env_dup = DupEnv(env);   /* duplicate env array and convert to lowercase*/ 
	PrintEnv(env_dup);
	free(env_dup);
	return 0;
}

/* duplicates env array and convert it to lowercase */
char **DupEnv(char *env[])
{
	int num_of_strings = 0;
	int counter = 0;
	int i = 0;
	char **env_dup = NULL;
	for (i=0; env[i] != NULL; ++i);      /*count how much rows we have in env*/
	num_of_strings = i+1;
	env_dup = (char **)malloc(num_of_strings*sizeof(char*)); /*rows*/
	if (NULL == env_dup)
	{
		return NULL;
	}
	for(i=0; i< num_of_strings-1; ++i)                        /*cols*/
	{
		env_dup[i] = (char*)malloc((strlen(env[i])+1)*sizeof(char));
	}
	if (NULL == *env_dup)
	{
			
		return NULL;
	}
	while (*env != NULL)	
	{
		strcpy(*env_dup, *env);
		ToLower(*env_dup);
		
		env++;
		env_dup++;
		counter++;
	}
	*env_dup = NULL;	/* last pointer in array is to NULL */
	
	return (env_dup - counter);
}

/* prints strings inside the ptr's array */
void PrintEnv(char **env)
{
	size_t i = 0;
	for (i=0; i<strlen(env[i]); ++i)
	{
		printf("%s",env[i]);
	} 
	
}	


/* convert a full string to lowercase */
void ToLower(char *str)
{
	while ('\0' != *str)
	{
		*str = tolower(*str);
		++str;
	}
}

