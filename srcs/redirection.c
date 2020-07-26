/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 11:45:17 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/26 16:56:58 by jinwkim          ###   ########.fr       */
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
	return (0);
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

int		get_redir(char **argv, int **fd_input, int **fd_output)
{
	int		input_idx;
	int		output_idx;
	int		idx;
	int		size;

	idx = 0;
	input_idx = 0;
	output_idx = 0;
	size = get_redir_out_size(argv);
	*fd_output = (int *)malloc(sizeof(int) * (size + 1));
	(*fd_output)[size] = 0;
	size = get_redir_input_size(argv);
	*fd_input = (int *)malloc(sizeof(int) * (size + 1));
	(*fd_input)[size] = 0;
	while (argv[idx] != 0)
	{
		if (ft_strcmp(argv[idx], ">") == 0)
		{
			if (check_redir(argv[++idx]) == 1)
			{
				(*fd_output)[output_idx] = open(argv[idx], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if ((*fd_output)[output_idx] == -1)
				{
					clear_redir(*fd_input, input_idx, 0, 0);
					return (clear_redir(*fd_output, output_idx, &(argv[idx]), errno));
				}
				output_idx++;
			}
			else
			{
				clear_redir(*fd_input, input_idx, 0, 0);
				return (clear_redir(*fd_output, output_idx, &(argv[idx]), 0));
			}
		}
		else if (ft_strcmp(argv[idx], ">>") == 0)
		{
			if (check_redir(argv[++idx]) == 1)
			{
				(*fd_output)[output_idx] = open(argv[idx], O_WRONLY | O_CREAT | O_APPEND, 0644);
				if ((*fd_output)[output_idx] == -1)
				{
					clear_redir(*fd_input, input_idx, 0, 0);
					return (clear_redir(*fd_output, output_idx, &(argv[idx]), errno));
				}
				output_idx++;
			}
			else
			{
				clear_redir(*fd_input, input_idx, 0, 0);
				return (clear_redir(*fd_output, output_idx, &(argv[idx]), 0));
			}
		}
		else if (ft_strcmp(argv[idx], "<") == 0)
		{
			if (check_redir(argv[++idx]) == 1)
			{
				(*fd_input)[input_idx] = open(argv[idx], O_RDONLY);
				if ((*fd_input)[input_idx] == -1)
				{
					clear_redir(*fd_output, output_idx, 0, 0);
					return (clear_redir(*fd_input, input_idx, &(argv[idx]), errno));
				}
				input_idx++;
			}
			else
			{
				clear_redir(*fd_output, output_idx, 0, 0);
				return (clear_redir(*fd_input, input_idx, &(argv[idx]), 0));
			}
		}
		idx++;
	}
	return (0);
}
