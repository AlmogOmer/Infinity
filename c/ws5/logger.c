#include <stdio.h>
#include <stdlib.h>		
#include <string.h>	

enum exit{success, failure} exit_status;
	
int IsCmdMatch(const char *cmd_to_match, const char *cmd);
int IsPrepend(const char *cmd_to_match, const char *cmd);
int IsAppend(const char *cmd_to_match, const char *cmd);

int Append(const char *fname, const char *txt);
int Remove(const char *fname, const char *txt);
int Count(const char *fname, const char *txt);
int Prepend(const char *fname, const char *txt);
int Exit(const char *fname, const char *txt);

struct cmd
{
	char *cmd_to_match;
	int (*CmpFunc)(const char *, const char *);
	int (*OptFunc)(const char *, const char *);
};

struct cmd cmd_arr[5] = 
{
	{"-remove\n", IsCmdMatch, Remove}, 
	{"-count\n", IsCmdMatch, Count}, 
	{"-exit\n", IsCmdMatch, Exit}, 
	{"<", IsPrepend, Prepend}, 
	{NULL, IsAppend, Append}
};
int main(int argc ,char **argv)
{

	int  i = 0;
	char str[100] = {0};
	while(1)
	{	
		if (NULL != fgets(str, 100, stdin))		
		{
			for (i = 0 ; ; ++i)
			{
				if (cmd_arr[i].CmpFunc(cmd_arr[i].cmd_to_match, str))
				{
					cmd_arr[i].OptFunc(argv[1], str);
					break;
				}
			}
		}	
	}

	return success;
}

int IsCmdMatch(const char *cmd_to_match, const char *cmd)
{
	return (0 == strcmp(cmd_to_match, cmd));
}

int IsPrepend(const char *cmd_to_match, const char *cmd)
{
	return (*cmd_to_match == *cmd); /* checks only first char to be '<' */
}

int IsAppend(const char *cmd_to_match, const char *cmd)
{
	return (1);		/* last comparison in array, always return TRUE */
}

	
int Append(const char *fname, const char *txt)
{
	FILE *file_ptr = fopen(fname, "a");
	if (NULL == file_ptr)
	{
		puts("failed to load file");
		return failure;
	}
	fputs(txt, file_ptr);
	fclose(file_ptr);
	return success;
}

int Remove(const char *fname, const char *txt)
{
	int check = 0;
	check = remove(fname);
	
	if (-1 == check)
	{
		puts("failed to remove file");
		return failure;
	}
	
	return success;
}

int Count(const char *fname, const char *txt)
{
	size_t counter = 0;
	int curr_char = 0;
	
	FILE *file_ptr = fopen(fname, "r");
	if (NULL == file_ptr)
	{
		puts("failed to load file");
		return failure;
	}
	
	curr_char = fgetc(file_ptr);		/* we check  */
	
	while (EOF != curr_char)
	{
		if ('\n' == curr_char)
		{
			++counter;
		}
		curr_char = fgetc(file_ptr);
	}
	
	printf("number of lines in the file: %lu\n", counter);
	fclose(file_ptr);
	
	return success;
}

int Prepend(const char *fname, const char *txt)
{
	FILE *tmp_file_ptr = NULL;
	FILE *file_ptr = NULL;
	int ch = 0;
	
	file_ptr = fopen(fname, "a+");
	if (NULL == file_ptr)
	{
		puts("failed to load file");
		return failure;
	}
	
	tmp_file_ptr = fopen("./tmp.txt", "a");	/* opening a tmp file */
	if (NULL == tmp_file_ptr)
	{
		puts("failed to prepend file");
		return failure;
	}
	
	fputs(txt + 1, tmp_file_ptr);		/* prepending the text */
	
	ch = fgetc(file_ptr);
	
	while (EOF != ch)			/* appending the sent file */
	{
		fputc(ch, tmp_file_ptr);
		ch = fgetc(file_ptr);
	}
	
	fclose(file_ptr);
	fclose(tmp_file_ptr);
	
	ch = rename("tmp.txt", fname);	/* rename overwrites the file */
	if (-1 == ch)
	{
		puts("failed to prepend file");
		return failure;
	}
	
	return success;
}

int Exit(const char *fname, const char *txt)
{
	exit(0);
}




