/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 16:39:00 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/29 17:05:02 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "execute_command.h"
#include "error.h"

char	**remove_redirection(char **argv)
{
	char	**removed;
	int		i;

	removed = (char **)malloc(sizeof(char *));
	removed[0] = NULL;
	i = 0;
	while (argv[i] != NULL)
	{
		if (!ft_strcmp(argv[i], "<") || !ft_strcmp(argv[i], ">") ||

				!ft_strcmp(argv[i], ">>"))
			i++;
		else
			removed = extend_argv(removed, ft_strdup(argv[i]));
		i++;
	}
	return (removed);
}

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

int		clear_redir_fd(int *fd_input, int *fd_out)
{
	if (fd_input != 0)
		free(fd_input);
	if (fd_out != 0)
		free(fd_out);
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
