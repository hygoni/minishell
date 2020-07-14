#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "get_next_line.h"

extern char **environ;

int		check_env_key(char *str, char *key)
{
	while ((*str != 0 && *str != '=') || *key != 0)
	{
		if (*str != *key)
			return (0);
		str++;
		key++;
	}
	return (1);
}

char	*get_env_value(char *src)
{
	char	*result;
	int		size;
	int		idx;
	int		idx_2;

	size = ft_strlen(src);
	idx = 0;
	while (src[idx] != '=' && src[idx] != 0)
		idx++;
	size = size - idx;
	result = (char *)malloc(sizeof(char) * size);
	idx_2 = 0;
	idx++;
	while (src[idx] != 0)
	{
		result[idx_2] = src[idx];
		idx++;
		idx_2++;
	}
	result[idx_2] = 0;
	return (result);
}

char	*make_prompt(char **env)
{
	char	*result;
	int		size;

	size = 0;
	result = 0;
	while (*env != 0)
	{
		if (check_env_key(*env, "USER") == 1)
		{
			result = get_env_value(*env);
			break ;
		}
		env++;
	}
	return (result);
}

int		main(void)
{
	char	*command;
	char	**new_argv;
	char	*prompt;
	pid_t	child;
	pid_t	pid;
	int		state;

	prompt = make_prompt(environ);
	child = 1;
	while (1)
	{
		if (child == 0)
		{
			if (execve(command, new_argv, environ) == -1)
			{
				fprintf(stderr, "error: %s\n", strerror(errno));
				return (1);
			}
		}
		if (child != 0)
		{
			write(1, prompt, ft_strlen(prompt));
			write(1, "% ", 2);
			get_next_line(1, &command);
			new_argv = ft_split(command, ' ');
			free(command);
			command = new_argv[0];
			child = fork();
			pid = wait(&state);
		}
	}
}
