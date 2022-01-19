#include <unistd.h>		/* for fork, exec.. */
#include <stdlib.h>		
#include <sys/wait.h>	/* for wait */
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main()
{
	pid_t pid;
	int child_status;
	size_t i;
	char *argv[50];
	char *token = NULL;
	const char s[2] = " ";
	char *buf = (char *)calloc(15,sizeof(char));

	while (1)
	{
		i = 0;
		scanf("%[^\n]%*c", buf);
    	
		token = strtok(buf, s);

		while(token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, s);
			++i;
		}

		argv[i] = NULL;
		
		if (0 == strcmp("exit", argv[0]))
		{
			exit(1);
		}
		
		pid = fork();

		if (-1 == pid)
		{
			printf ("forking faild\n");
			exit(1);
		}
		
		else if (0 == pid)
		{
			execvp(argv[0], argv);
			exit(1);
		}
		
		else
		{
			child_status = 0;
			wait(&child_status);
			
		}
	}

	free(buf);
	return 0;
}


