/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 11:45:17 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/28 14:17:15 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "error.h"

int		check_redir(char *next)
{
	if (next != 0 && *next != 0)
	{
		if (ft_strcmp(next, "<") == 0)
			return (0);
		else if (ft_strcmp(next, "<<") == 0)
			return (0);
		else if (ft_strcmp(next, ">") == 0)
			return (0);
		else
			return (1);
	}
	return (0);
}

int		clear_redir(int *arr, int end, char **err_file, int error)
{
	int		idx;

	idx = 0;
	while (idx < end)
	{
		close(arr[idx]);
		idx++;
	}
	free(arr);
	if (error != 0)
		return (error_msg_param("minishell", *err_file, strerror(error)));
	if (err_file != 0 && *err_file == 0)
		return (error_msg_parse("\\n"));
	else if (err_file != 0 && check_redir(*err_file) == 0)
		return (error_msg_parse(*err_file));
	return (1);
}

int		get_redir_out_size(char **argv)
{
	int		idx;
	int		size;

	idx = 0;
	size = 0;
	while (argv[idx] != 0)
	{
		if (ft_strcmp(argv[idx], ">") == 0)
		{
			if (check_redir(argv[idx + 1]) == 1)
				size++;
		}
		else if (ft_strcmp(argv[idx], ">>") == 0)
		{
			if (check_redir(argv[idx + 1]) == 1)
				size++;
		}
		idx++;
	}
	return (size);
}

int		get_redir_input_size(char **argv)
{
	int		idx;
	int		size;

	idx = 0;
	size = 0;

	while (argv[idx] != 0)
	{
		if (ft_strcmp(argv[idx], "<") == 0)
		{
			if (check_redir(argv[idx + 1]) == 1)
				size++;
		}
		idx++;
	}
	return (size);
}

int		insert_fd(char **argv, int	**fd, int *fd_idx, int type)
{
	int		idx;

	idx = (type == 2) ? 0 : 1;
	if (check_redir(*argv) == 1)
	{
		if (type == 0)
			fd[idx][fd_idx[idx]] = open(*argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (type == 1)
			fd[idx][fd_idx[idx]] = open(*argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd[idx][fd_idx[idx]] = open(*argv, O_RDONLY);
		if ((fd[idx])[fd_idx[idx]] == -1)
		{
			clear_redir(fd[(idx + 1) % 2], fd_idx[(idx + 1) % 2], 0, 0);
			return (clear_redir(fd[idx], fd_idx[idx], argv, errno));
		}
		fd_idx[idx] = fd_idx[idx] + 1;
	}
	else
	{
		clear_redir(fd[(idx + 1) % 2], fd_idx[(idx + 1) % 2], 0, 0);
		return (clear_redir(fd[idx], fd_idx[idx], argv, errno));
	}
	return (0);
}

int		init_fd_arr(int **fd, char **argv, int **fd_input, int **fd_output)
{
	int		size;

	size = get_redir_out_size(argv);
	if ((*fd_output = (int *)malloc(sizeof(int) * (size + 1))) == 0)
		return (error_msg("minishell", "malloc fail"));
	(*fd_output)[size] = 0;
	size = get_redir_input_size(argv);
	if ((*fd_input = (int *)malloc(sizeof(int) * (size + 1))) == 0)
	{
		free(*fd_output);
		return (error_msg("minishell", "malloc fail"));
	}
	(*fd_input)[size] = 0;
	fd[0] = *fd_input;
	fd[1] = *fd_output;
	return (0);
}

int		get_redir(char **argv, int **fd_input, int **fd_output)
{
	int		fd_idx[2];
	int		*fd[2];
	int		idx;
	int		result;

	idx = 0;
	fd_idx[0] = 0;
	fd_idx[1] = 0;
	result = 0;
	if ((result = init_fd_arr(fd, argv, fd_input, fd_output)) != 0)
		return (result);
	result = 0;
	while (argv[idx] != 0)
	{
		if (ft_strcmp(argv[idx], ">") == 0)
			result = insert_fd(&(argv[++idx]), fd, fd_idx, 0);
		else if (ft_strcmp(argv[idx], ">>") == 0)
			result = insert_fd(&(argv[++idx]), fd, fd_idx, 1); 
		else if (ft_strcmp(argv[idx], "<") == 0)
			result = insert_fd(&(argv[++idx]), fd, fd_idx, 2);
		if (result != 0)
			return (result);
		idx++;
	}
	return (0);
}
