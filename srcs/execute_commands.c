/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:30:18 by jinwkim           #+#    #+#             */
/*   Updated: 2020/08/02 14:01:53 by jinwkim          ###   ########.fr       */
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

extern int g_status;
extern pid_t	g_child;

int		write_fd(int write_fd)
{
	int		read_fd;
	char	c;

	if ((read_fd = open(".tmp", O_RDONLY)) < 0)
		return (1);
	while (read(read_fd, &c, 1) > 0)
		write(write_fd, &c, 1);
	close(read_fd);
	return (0);
}

int		read_write_fd(int read_fd, int write_fd)
{
	char	c;

	while (read(read_fd, &c, 1) > 0)
		write(write_fd, &c, 1);
	close(read_fd);
	return (0);
}

int		pipe_recursive(int idx, int *child_fd, char ***argv, char ***env)
{
	if (idx != 0)
	{
		pipe(child_fd);
		g_child = fork();
		if (g_child == 0)
			execute_pipe(idx - 1, child_fd, argv, env);
	}
	return (0);
}

int		execute_pipe(int idx, int *fd, char ***argv, char ***env)
{
	char	**new_argv;
	int		child_fd[2];
	int		*fd_arr[2];
	int		tmp[2];

	dup2(fd[1], 1);
	tmp[1] = fd[1];
	pipe_recursive(idx, child_fd, argv, env);
	if ((g_status = get_redir(argv[idx], &(fd_arr[0]), &(fd_arr[1]))) != 0)
		exit(g_status);
	new_argv = remove_redirection(argv[idx]);
	if (idx != 0)
		close(child_fd[1]);
	init_redir_input(idx != 0 ? 2 : 0, fd_arr, tmp,
			idx != 0 ? child_fd : fd);
	init_redir_output(1, fd_arr[1], tmp, fd);
	close(fd[0]);
	execute_command(new_argv, env);
	clean_arg(0, 0, &new_argv, 0);
	clear_redir_fd(fd_arr[0], fd_arr[1]);
	wait(&g_status);
	exit(0);
}

/*
** execute multiple pipe command
** last command is execute this shell, other command is execute child
*/

int		execute_commands(char ***argv, char ***env)
{
	int		len;
	int		fd[2];

	len = get_strarr_size3(argv);
	if (check_pipe(argv, env, len, fd) == 1)
		return (1);
	else
		return (0);
}
