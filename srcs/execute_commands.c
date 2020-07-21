/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:30:18 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/21 16:58:26 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "execute_command.h"
#include "ft_environ.h"
#include "libft.h"

int		execute_pipe(int idx, int *fd, char **argv, char ***env)
{
	pid_t	child;
	int		status;
	char	**new_argv;

	if (idx != 0)
	{
		child = fork();
		if (child == 0)
			execute_pipe(idx - 1, fd, argv, env);
		else
			wait(&status);
		new_argv = ft_split(argv[idx], ' ');
		execute_command(new_argv, env);
		close(fd[0]);
		clean_arg(0, 0, &new_argv, 0);
		exit(0);
	}
	else
	{
		close(fd[0]);
		new_argv = ft_split(argv[idx], ' ');
		execute_command(new_argv, env);
		exit(0);
	}
}

int		execute_commands(char **argv, char ***env)
{
	pid_t	child;
	int		status;
	int		len;
	char	**new_argv;
	int		fd[2];
	int		origin_stdin;

	len = get_strarr_size(argv);
	origin_stdin = dup(0);
	if (len > 1)
	{
		pipe(fd);
		dup2(fd[0], 0);
		child = fork();
		if (child == 0)
		{
			dup2(fd[1], 1);
			execute_pipe(len - 2, fd, argv, env);
			exit(0);
		}
		wait(&status);
		close(fd[1]);
	}
	new_argv = ft_split(argv[len - 1], ' ');
	execute_command(new_argv, env);
	if (len > 1)
	{
		close(fd[0]);
		dup2(origin_stdin, 0);
	}
	close(origin_stdin);
	clean_arg(0, 0, &new_argv, 0);
	return (1);
}
