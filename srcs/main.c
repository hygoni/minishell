/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 19:37:25 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/10 20:17:14 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_environ.h"
#include "builtin.h"
#include "error.h"
#include "minishell.h"
#include "execute_command.h"
#include "parser.h"
#include "signals.h"

#define EXE_NAME	"minishell"
#define COMMAND_NOT_FOUND	"command not found"

pid_t	g_child;
int		g_status;
int		g_interrupted = 0;
char	*g_prompt;
char	*g_process_name = "minishell";

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

char	*execute_binary_sub(char **argv, char **env)
{
	char	*exe_path;

	if ((exe_path = find_exec(argv[0], env)) == NULL)
	{
		g_status = 127;
		error_msg_param(EXE_NAME, argv[0], COMMAND_NOT_FOUND);
		return (NULL);
	}
	return (exe_path);
}

void	execute_binary(char **argv, char **env)
{
	pid_t	child;
	char	*exe_path;
	int		status;

	if ((exe_path = execute_binary_sub(argv, env)) == NULL)
		return ;
	child = 1;
	if (child != 0)
	{
		child = fork();
		g_child = wait(&status);
		if (g_interrupted == 0)
			g_status = status;
		else
			g_interrupted = 0;
		free(exe_path);
	}
	if (child == 0)
	{
		if (execve(exe_path, argv, env) == -1)
		{
			error_msg(EXE_NAME, strerror(errno));
			exit(errno);
		}
	}
}

int		execute_command(char **argv, char ***env)
{
	char	*command;
	int		size;

	if ((command = argv[0]) == 0)
		return (1);
	g_process_name = command;
	size = get_strarr_size(argv);
	if (ft_strcmp(command, "echo") == 0)
		g_status = ft_echo(size, argv);
	else if (ft_strcmp(command, "cd") == 0)
		g_status = ft_cd(size, argv, *env);
	else if (ft_strcmp(command, "pwd") == 0)
		g_status = ft_pwd(size, *env);
	else if (ft_strcmp(command, "env") == 0)
		g_status = ft_env(*env);
	else if (ft_strcmp(command, "export") == 0)
		g_status = ft_export(size, argv, env);
	else if (ft_strcmp(command, "unset") == 0)
		g_status = ft_unset(size, argv, env);
	else if (ft_strcmp(command, "exit") == 0)
		g_status = ft_exit(argv, size);
	else
		execute_binary(argv, *env);
	g_process_name = EXE_NAME;
	return (1);
}

int		main(int argc, char **argv, char **environ)
{
	char	*command;
	char	**env;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	if (init_main(&g_prompt, environ, &env) == 0)
		return (0);
	while (1)
	{
		write(1, g_prompt, ft_strlen(g_prompt));
		if (get_next_line(0, &command) == 0 && *command == 0)
		{
			free(command);
			break ;
		}
		if (command != 0)
		{
			parse_commands(command, &env);
			free(command);
		}
	}
	clean_arg(&g_prompt, 0, 0, &env);
}
