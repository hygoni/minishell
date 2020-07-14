#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_environ.h"

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

char	*make_prompt(char **env)
{
	char	*result;
	char	*sub;

	result = 0;
	sub = get_env_value(env, "USER");
	result = ft_strjoin(sub, "% ");
	return (result);
}

void	execute_binary(char **argv, char **env)
{
	pid_t	child;
	pid_t	pid;
	int		state;

	child = 1;
	if (child == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			fprintf(stderr, "error: %s\n", strerror(errno));
			return ;
		}
	}
	if (child != 0)
	{
		child = fork();
		pid = wait(&state);
	}
}

void	execute_command(char **argv, char ***env)
{
	char	*command;
	int		len;
	int		size;

	command = argv[0];
	size = get_strarr_size(argv);
	len = ft_strlen(command);
	if (ft_strncmp(command, "echo", len > 4 ? len : 4) == 0)
		printf("echo command\n");
	else if (ft_strncmp(command, "cd", len > 2 ? len : 2) == 0)
		printf("cd command\n");
	else if (ft_strncmp(command, "pwd", len > 3 ? len : 3) == 0)
		printf("cd command\n");
	else if (ft_strncmp(command, "env", len > 3 ? len : 3) == 0)
		builtin_env(*env);
	else if (ft_strncmp(command, "export", len > 6 ? len : 6) == 0)
		builtin_export(size, argv, env);
	else if (ft_strncmp(command, "unset", len > 5 ? len : 5) == 0)
		builtin_unset(size, argv, env);
	else if (ft_strncmp(command, "exit", len > 4 ? len : 4) == 0)
		printf("exit command\n");
	else
		execute_binary(argv, *env);
}

int		main(void)
{
	char	*command;
	char	**new_argv;
	char	**env;
	char	*prompt;
	int		len;

	prompt = make_prompt(environ);
	len = get_strarr_size(environ);
	env = cpy_env(environ, len);
	while (1)
	{
		write(1, prompt, ft_strlen(prompt));
		get_next_line(1, &command);
		new_argv = ft_split(command, ' ');
		free(command);
		command = 0;
		execute_command(new_argv, &env);
	}
}
