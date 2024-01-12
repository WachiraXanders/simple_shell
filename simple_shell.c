#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$"
/**
	*executeCommand - Executes the entered command.
	*@input: The command to execute.
	*/
void executeCommand(char *input)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		execlp(input, input, (char *)NULL);
		perror("shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
/**
	*displayPrompt - Displays the shell prompt.
	*/
void displayPrompt(void)
{
	printf("%s", PROMPT);
}

/**
	*main - Entry point for the shell.
	*Return: Always 0.
	*/
int main(void)
{
	char *input = NULL;
	size_t len = 0;

	while (1)
	{
		displayPrompt();

		if (getline(&input, &len, stdin) == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("getline");
			exit(EXIT_FAILURE);
		}
		if (strcmp(input, "exit\n") == 0)
		{
			printf("\n");
			break;
		}

		if (input[len - 1] == '\n')
		{
			input[len - 1] = '\0';
		}
		executeCommand(input);
	}
	free(input);
	return (0);
}
