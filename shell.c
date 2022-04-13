#include "shell.h"

/**
 * main - main function.
 * Return: Always 0 (Succes).
 */

int main(int ac, char **av, char **env)
{
	(void) ac, (void) av;
	char *path = _findpath_(env), **tok_path;
	char *line = NULL, *EXIT = "exit", **array_token;
	size_t len = 1024;
	int status;
	pid_t child_pid;

	line = (char *)malloc(len * sizeof(char));
	if (line == NULL)
		perror("Unable allocate buffer"), exit(EXIT_FAILURE);

	while (1)
	{
		printf("devspjm@holberton $ ");
		if ((getline(&line, &len, stdin)) == -1)
			_exit_(line);
		if (line)
		{
			array_token = _strtok_(line, ' '), tok_path = _strtok_(path, ':');
			if (!_strcmp_(array_token[0], EXIT))
			{
				_freestrs(array_token), _freestrs(tok_path), _exit_(line);
			}
			else if (!_builtin_(tok_path, array_token[0]))
			{
				child_pid = fork();
				if (child_pid == -1)
					perror("Error:");
				else if (child_pid == 0)
				{
					if (execve(array_token[0], array_token, NULL) == -1)
						perror("Error:");
				}
				else
					wait(&status);
			}
			else
				printf("sh : %s: command not found\n", array_token[0]);
			_freestrs(array_token);
		}
	}
	_freestrs(tok_path), free(path), _exit_(line);
	return (0);
}
