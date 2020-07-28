/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 19:37:25 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/26 18:09:24 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_environ.h"
#include "builtin.h"
#include "error.h"
#include "minishell.h"
#include "execute_command.h"
#include "parser.h"

#define EXE_NAME	"minishell"
#define COMMAND_NOT_FOUND	"command not found"

extern char	**environ;
int		g_status;

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

void	execute_binary(char **argv, char **env)
{
	pid_t	child;
	pid_t	pid;
	char	*exe_path;

	if ((exe_path = find_exec(argv[0], env)) == NULL)
	{
		error_msg_param(EXE_NAME, COMMAND_NOT_FOUND, argv[0]);
		return ;
	}
	child = 1;
	if (child != 0)
	{
		child = fork();
		pid = wait(&g_status);
		free(exe_path);
	}
	if (child == 0)
	{
		if (execve(exe_path, argv, env) == -1)
		{
			error_msg(EXE_NAME, strerror(errno));
			ft_exit(ft_itoa(errno));
		}
	}
}

int		execute_command(char **argv, char ***env)
{
	char	*command;
	int		len;
	int		size;

	if ((command = argv[0]) == 0)
		return (1);
	size = get_strarr_size(argv);
	len = ft_strlen(command);
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
		g_status = ft_exit(argv[1]);
	else
		execute_binary(argv, *env);
	return (1);
}

int		main(void)
{
	char	*command;
	char	**env;
	char	*prompt;

	if (init_main(&prompt, environ, &env) == 0)
		return (0);
	while (1)
	{
		write(1, prompt, ft_strlen(prompt));
		if (get_next_line(0, &command) == 0 && *command == 0)
		{
			free(command);
			break ;
		}
		parse_commands(command, &env);
		free(command);
	}
	clean_arg(0, 0, 0, &env);
}
