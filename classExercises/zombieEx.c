#include <stdio.h>
#include <unistd.h>
#define TRUE 1
int g_var=0;

int main(void) 
{
	while(TRUE) 
	{

		char* command = "ls";
		char* parameters[] = {"ls", "-l"};
		int status = 0;
		/*type_prompt();

		read_command(command, parameters);
		*/
		if (fork() != 0) 
		{

			/* Parent Code */

			waitpid(-1, &status, 0);

		} 
		else 
		{

		/* Child code */
			
			execvp(command, parameters);

		}

	}



/*
	int n, i, l_var = 0;
	n = fork();
	if (n < 0)
	{


	} 
	else if (n > 0)
	{
		for(i = 0; i < 30; i++)
		{
			++g_var; 
			printf("n= %d g_var=%d\n", n, g_var);
	
			++l_var; 
			printf("n= %d l_var=%d\n", n, l_var);
		
			sleep(10);
		}
	
	} 
	else
	{ 
		for(i = 0; i < 30; i++)
		{
			--g_var; 
			printf("n= %d g_var=%d\n", n, g_var);
	
			--l_var; 
			printf("n= %d l_var=%d\n", n, l_var);
			
			sleep(1);
		}

	}
*/
}
