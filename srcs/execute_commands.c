/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:30:18 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/26 02:11:00 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "execute_command.h"
#include "ft_environ.h"
#include "libft.h"
#include "redirection.h"

int		execute_pipe(int idx, int *fd, char **argv, char ***env)
{
	pid_t	child;
	int		status;
	char	**new_argv;
	int		child_fd[2];
	int		*fd_arr_input;
	int		*fd_arr_output;
	int		arr_idx;
	char	*file;

	if (idx != 0)
	{
		pipe(child_fd);
		dup2(child_fd[0], 0);
		child = fork();
		if (child == 0)
			execute_pipe(idx - 1, child_fd, argv, env);
		else
			wait(&status);
		new_argv = ft_split(argv[idx], ' ');
		close(child_fd[1]);
		close(fd[0]);
		dup2(fd[1], 1);
		if ((status = get_redir(new_argv, &fd_arr_input, &fd_arr_output)) != 0)
			exit(status);
		execute_command(new_argv, env);
		arr_idx = 0;
		while (fd_arr_input[arr_idx] != 0)
		{
			dup2(fd_arr_input[arr_idx], 0);
			execute_command(new_argv, env);
			close(fd_arr_input[arr_idx]);
			arr_idx++;
		}
		clean_arg(0, 0, &new_argv, 0);
		exit(0);
	}
	else
	{
		new_argv = ft_split(argv[idx], ' ');
		close(fd[0]);
		dup2(fd[1], 1);
		if ((status = get_redir(new_argv, &fd_arr_input, &fd_arr_output)) != 0)
			exit(status);
		execute_command(new_argv, env);
		arr_idx = 0;
		while (fd_arr_input[arr_idx] != 0)
		{
			dup2(fd_arr_input[arr_idx], 0);
			execute_command(new_argv, env);
			close(fd_arr_input[arr_idx]);
			arr_idx++;
		}
		exit(0);
	}
}

/*
** execute multiple pipe command
** last command is execute this shell, other command is execute child
*/

int		execute_commands(char **argv, char ***env)
{
	pid_t	child;
	int		status;
	int		len;
	char	**new_argv;
	int		fd[2];
	int		origin_stdin;
	int		*fd_arr_input;
	int		*fd_arr_output;
	int		arr_idx;

	len = get_strarr_size(argv);
	origin_stdin = dup(0);
	if (len > 1)
	{
		pipe(fd);
		dup2(fd[0], 0);
		child = fork();
		if (child == 0)
		{
			execute_pipe(len - 2, fd, argv, env);
			exit(0);
		}
		wait(&status);
		close(fd[1]);
	}
	new_argv = ft_split(argv[len - 1], ' ');
	if ((status = get_redir(new_argv, &fd_arr_input, &fd_arr_output)) != 0)
		exit(status);
	execute_command(new_argv, env);
	arr_idx = 0;
	while (fd_arr_input[arr_idx] != 0)
	{
		dup2(fd_arr_input[arr_idx], 0);
		execute_command(new_argv, env);
		close(fd_arr_input[arr_idx]);
		arr_idx++;
	}
	if (len > 1)
	{
		close(fd[0]);
		dup2(origin_stdin, 0);
	}
	close(origin_stdin);
	clean_arg(0, 0, &new_argv, 0);
	return (1);
}
