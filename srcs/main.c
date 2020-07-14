#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_environ.h"
#include "builtin.h"

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

int		execute_command(char **argv, char ***env)
{
	char	*command;
	int		len;
	int		size;
	
	//a b c d
	command = argv[0];
	size = get_strarr_size(argv);
	len = ft_strlen(command);
	if (ft_strcmp(command, "echo") == 0)
		echo(size, argv);
	else if (ft_strcmp(command, "cd") == 0)
		cd(size, argv, *env);
	else if (ft_strcmp(command, "pwd") == 0)
		pwd(size, argv, *env);
	else if (ft_strcmp(command, "env") == 0)
		_env(*env);
	else if (ft_strcmp(command, "export") == 0)
		_export(size, argv, env);
	else if (ft_strcmp(command, "unset") == 0)
		_unset(size, argv, env);
	else if (ft_strcmp(command, "exit") == 0)
	{
		if (argv[1] != 0)
			_exit(ft_atoi(argv[1]));
		else
			_exit(0);
	}
	else
		execute_binary(argv, *env);
	return (1);
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
		if (execute_command(new_argv, &env) == 0)
		{
			clean_arg(prompt, 0, new_argv, env);
			break ;
		}
		clean_arg(0, 0, new_argv, 0);
	}
	printf("program end\n");
}
