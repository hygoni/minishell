/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:30:18 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/21 13:43:55 by jinwkim          ###   ########.fr       */
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

	//dup2(fd[1], 1);
	//dup2(fd[0], 0);
	if (idx != 0)
	{
		child = fork();
		if (child == 0)
			execute_pipe(idx - 1, fd, argv, env);
		else
			wait(&status);
		new_argv = ft_split(argv[idx], ' ');
		execute_command(new_argv, env);
		clean_arg(0, 0, &new_argv, 0);
		exit(0);
	}
	else
	{
		new_argv = ft_split(argv[idx], ' ');
		execute_command(new_argv, env);
		clean_arg(0, 0, &new_argv, 0);
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

	len = get_strarr_size(argv);
	pipe(fd);
	if (len > 1)
	{
		child = fork();
		if (child == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			fd[0] = dup(0);
			execute_pipe(len - 2, fd, argv, env);
			exit(0);
		}
		wait(&status);
	}
	//read fd0] and cpy stdin
	new_argv = ft_split(argv[len - 1], ' ');
	execute_command(new_argv, env);
	clean_arg(0, 0, &new_argv, 0);
	char c;
	while (read(fd[0], &c, 1) > 0)
	{
		write(1, &c, 1);
	}
	return (1);
}
