/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:02:43 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/28 02:44:11 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "execute_command.h"
#include "ft_environ.h"
#include "redirection.h"

int		init_redir_input(int len, int *fd_input, int *tmp, int *fd)
{
	int		arr_idx;
	char	c;

	arr_idx = 0;
	tmp[0] = open(".input", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (len > 1)
	{
		while (read(fd[0], &c, 1) > 0)
			write(tmp[0], &c, 1);
	}
	while (fd_input[arr_idx] != 0)
		read_write_fd(fd_input[arr_idx++], tmp[0]);
	close(tmp[0]);
	tmp[0] = open(".input", O_RDONLY);
	dup2(tmp[0], 0);
	tmp[1] = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(tmp[1], 1);
	return (0);
}

int		init_redir_output(int *fd_out, int *origin)
{
	int		arr_idx;

	dup2(origin[0], 0);
	close(origin[0]);
	arr_idx = 0;
	while (fd_out[arr_idx] != 0)
	{
		write_fd(fd_out[arr_idx]);
		close(fd_out[arr_idx]);
		arr_idx++;
	}
	dup2(origin[1], 1);
	close(origin[1]);
	if (fd_out[0] == 0)
		write_fd(1);
	return (0);
}

int		pipe_command(char ***argv, char ***env, int len, int *fd)
{
	pid_t	child;
	int		status;

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
	return (0);
}

int		check_pipe(char ***argv, char ***env, int len, int *fd)
{
	int		check_redir;
	int		origin[2];
	int		**fd_arr;
	char	**new_argv;
	int		tmp[2];

	origin[0] = dup(0);
	origin[1] = dup(1);
	fd_arr = (int **)malloc(sizeof(int *) * 2);
	if (len > 1)
		pipe_command(argv, env, len, fd);
	if ((check_redir =
				get_redir(argv[len - 1], &(fd_arr[0]), &(fd_arr[1]))) != 0)
		return (1);
	new_argv = remove_redirection(argv[len - 1]);
	init_redir_input(len, fd_arr[0], tmp, fd);
	execute_command(new_argv, env);
	if (len > 1)
		close(fd[0]);
	else if (len == 1 && fd_arr[0][0] != 0)
		close(tmp[0]);
	close(tmp[1]);
	init_redir_output(fd_arr[1], origin);
	return (0);
}
