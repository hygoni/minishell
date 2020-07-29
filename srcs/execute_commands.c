/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:30:18 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/29 23:06:52 by jinwkim          ###   ########.fr       */
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
		else
			wait(&g_status);
	}
	return (0);
}

int		execute_pipe(int idx, int *fd, char ***argv, char ***env)
{
	char	**new_argv;
	int		child_fd[2];
	int		*fd_arr[2];
	int		tmp[2];

	pipe_recursive(idx, child_fd, argv, env);
	if ((g_status = get_redir(argv[idx], &(fd_arr[0]), &(fd_arr[1]))) != 0)
		exit(g_status);
	new_argv = remove_redirection(argv[idx]);
	if (idx != 0)
	{
		close(child_fd[1]);
		init_redir_input(2, fd_arr, tmp, child_fd);
		close(fd[0]);
	}
	else
		init_redir_input(0, fd_arr, child_fd, fd);
	execute_command(new_argv, env);
	if (idx != 0)
		close(tmp[1]);
	init_redir_output(0, fd_arr[1], fd);
	clean_arg(0, 0, &new_argv, 0);
	clear_redir_fd(fd_arr[0], fd_arr[1]);
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
