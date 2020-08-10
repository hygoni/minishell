/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:02:43 by jinwkim           #+#    #+#             */
/*   Updated: 2020/08/10 20:47:53 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "execute_command.h"
#include "ft_environ.h"
#include "redirection.h"

extern pid_t	g_child;
extern int		g_status;

void	close_pipe(int *fd, int *child, int *tmp, int type)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (child[1] != -1)
		close(child[1]);
	if (child[0] != -1)
		close(child[0]);
	if (tmp[0] != -1)
		close(tmp[0]);
	if (tmp[1] != -1)
		close(tmp[1]);
	if (type == 0)
	{
		close(0);
		close(1);
	}
}

int		init_redir_input(int type, int **fd_arr, int *tmp, int *fd)
{
	int		arr_idx;

	arr_idx = 0;
	tmp[0] = -1;
	tmp[1] = -1;
	if (type > 1)
	{
		dup2(fd[0], 0);
		tmp[0] = fd[0];
	}
	while (fd_arr[0][arr_idx] != 0)
	{
		if (arr_idx > 0)
			close(fd_arr[0][arr_idx - 1]);
		dup2(fd_arr[0][arr_idx++], 0);
		tmp[0] = fd_arr[0][arr_idx - 1];
	}
	return (0);
}

int		init_redir_output(int type, int *fd_out, int *tmp, int *fd)
{
	int		arr_idx;

	arr_idx = 0;
	if (type == 1)
	{
		dup2(fd[1], 1);
		tmp[1] = fd[1];
	}
	while (fd_out[arr_idx] != 0)
	{
		if (arr_idx > 0)
			close(fd_out[arr_idx - 1]);
		dup2(fd_out[arr_idx++], 1);
		tmp[1] = fd_out[arr_idx - 1];
	}
	return (0);
}

int		pipe_command(char ***argv, char ***env, int len, int *fd)
{
	pipe(fd);
	g_child = fork();
	if (g_child == 0)
	{
		execute_pipe(len - 2, fd, argv, env);
		exit(0);
	}
	close(fd[1]);
	return (0);
}

int		check_pipe(char ***argv, char ***env, int len, int *fd)
{
	int		check_redir;
	int		origin[2];
	int		*fd_arr[2];
	char	**new_argv;
	int		tmp[2];

	origin[0] = dup(0);
	origin[1] = dup(1);
	if (len > 1)
		pipe_command(argv, env, len, fd);
	if ((check_redir =
				get_redir(argv[len - 1], &(fd_arr[0]), &(fd_arr[1]))) != 0)
		return (1);
	new_argv = remove_redirection(argv[len - 1]);
	init_redir_input(len, fd_arr, tmp, fd);
	init_redir_output(0, fd_arr[1], tmp, fd);
	close(fd[1]);
	len = execute_command(new_argv, env);
	clear_redir_fd(fd_arr[0], fd_arr[1]);
	dup2(origin[0], 0);
	dup2(origin[1], 1);
	close_pipe(tmp, fd, origin, 1);
	clean_arg(0, 0, &new_argv, 0);
	(len >= 0) ? wait(&g_status) : 0;
	return (0);
}
