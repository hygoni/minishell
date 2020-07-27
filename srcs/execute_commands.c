/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:30:18 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/27 18:01:52 by jinwkim          ###   ########.fr       */
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

char	**remove_redirection(char **argv)
{
	char	**removed;
	int		i;

	removed = (char**)malloc(sizeof(char*));
	removed[0] = NULL;
	i = 0;
	while (argv[i] != NULL)
	{
		if (!ft_strcmp(argv[i], "<") || !ft_strcmp(argv[i], ">") ||
				!ft_strcmp(argv[i], ">>"))
			i++;
		else
		{
			removed = extend_argv(removed, ft_strdup(argv[i]));
		}
		i++;
	}
	return (removed);
}

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

int		execute_pipe(int idx, int *fd, char ***argv, char ***env)
{
	pid_t	child;
	int		status;
	char	**new_argv;
	int		child_fd[2];
	int		*fd_arr_input;
	int		*fd_arr_output;
	int		arr_idx;
	int		tmp_fd;

	if (idx != 0)
	{
		pipe(child_fd);
		dup2(child_fd[0], 0);
		child = fork();
		if (child == 0)
			execute_pipe(idx - 1, child_fd, argv, env);
		else
			wait(&status);
		new_argv = argv[idx];
		if ((status = get_redir(new_argv, &fd_arr_input, &fd_arr_output)) != 0)
			exit(status);
		new_argv = remove_redirection(new_argv);
		arr_idx = 0;
		while (fd_arr_input[arr_idx] != 0)
		{
			read_write_fd(fd_arr_input[arr_idx], child_fd[0]);
			arr_idx++;
		}
		close(child_fd[1]);
		close(fd[0]);
		tmp_fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(tmp_fd, 1);
		execute_command(new_argv, env);
		arr_idx = 0;
		close(tmp_fd);
		while (fd_arr_output[arr_idx] != 0)
		{
			write_fd(fd_arr_output[arr_idx]);
			close(fd_arr_output[arr_idx]);
			arr_idx++;
		}
		write_fd(fd[1]);
		clean_arg(0, 0, &new_argv, 0);
		exit(0);
	}
	else
	{
		new_argv = argv[idx];
		arr_idx = 0;
		if ((status = get_redir(new_argv, &fd_arr_input, &fd_arr_output)) != 0)
			exit(status);
		new_argv = remove_redirection(new_argv);
		child_fd[0] = open(".input", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while (fd_arr_input[arr_idx] != 0)
		{
			read_write_fd(fd_arr_input[arr_idx], child_fd[0]);
			arr_idx++;
		}
		close(child_fd[0]);
		child_fd[0] = open(".input", O_RDONLY);
		dup2(child_fd[0], 0);
		close(fd[0]);
		tmp_fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(tmp_fd, 1);
		execute_command(new_argv, env);
		arr_idx = 0;
		close(tmp_fd);
		while (fd_arr_output[arr_idx] != 0)
		{
			write_fd(fd_arr_output[arr_idx]);
			close(fd_arr_output[arr_idx]);
			arr_idx++;
		}
		write_fd(fd[1]);
		close(child_fd[0]);
		exit(0);
	}
}

/*
** execute multiple pipe command
** last command is execute this shell, other command is execute child
*/

int		execute_commands(char ***argv, char ***env)
{
	pid_t	child;
	int		status;
	int		len;
	char	**new_argv;
	int		fd[2];
	int		origin_stdin;
	int		origin_stdout;
	int		*fd_arr_input;
	int		*fd_arr_output;
	int		arr_idx;
	int		tmp_fd[2];

	len = get_strarr_size3(argv);
	origin_stdin = dup(0);
	origin_stdout = dup(1);
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
	if ((status = get_redir(argv[len - 1], &fd_arr_input, &fd_arr_output)) != 0)
		exit(status);
	new_argv = remove_redirection(argv[len - 1]);
	arr_idx = 0;
	if (len == 1 && fd_arr_input[0] != 0)
	{
		tmp_fd[0] = open(".input", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while (fd_arr_input[arr_idx] != 0)
		{
			read_write_fd(fd_arr_input[arr_idx], tmp_fd[0]);
			arr_idx++;
		}
		close(tmp_fd[0]);
		tmp_fd[0] = open(".input", O_RDONLY);
		dup2(tmp_fd[0], 0);
	}
	else if (len > 1)
	{
		while (fd_arr_input[arr_idx] != 0)
		{
			read_write_fd(fd_arr_input[arr_idx], fd[0]);
			arr_idx++;
		}
	}
	tmp_fd[1] = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(tmp_fd[1], 1);
	execute_command(new_argv, env);
	if (len > 1)
	{
		close(fd[0]);
		dup2(origin_stdin, 0);
	}
	else if (len == 1 && fd_arr_input[0] != 0)
	{
		close(tmp_fd[0]);
		dup2(origin_stdin, 0);
	}
	close(origin_stdin);
	arr_idx = 0;
	close(tmp_fd[1]);
	while (fd_arr_output[arr_idx] != 0)
	{
		write_fd(fd_arr_output[arr_idx]);
		close(fd_arr_output[arr_idx]);
		arr_idx++;
	}
	dup2(origin_stdout, 1);
	close(origin_stdout);
	write_fd(1);
	clean_arg(0, 0, &new_argv, 0);
	return (1);
}
