/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:30:18 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/19 16:48:19 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "execute_command.h"
#include "ft_environ.h"
#include "libft.h"

int		execute_pipe(int idx, char **argv, char ***env)
{
	pid_t	child;
	int		status;

	if (idx != 0)
	{
		child = fork();
		if (child == 0)
			execute_pipe(idx - 1, argv, env);
		else
			wait(&status);
		printf("%s\n", argv[idx]);
		printf("%d child exit\n", idx);
		exit(0);
	}
	else
	{
		printf("%s\n", argv[idx]);
		printf("last child exit\n");
		exit(0);
	}
}

int		execute_commands(char **argv, char ***env)
{
	pid_t	child;
	int		status;
	int		len;
	char	**new_argv;

	len = get_strarr_size(argv);
	if (len > 1)
	{
		child = fork();
		if (child == 0)
		{
			execute_pipe(len - 2, argv, env);
			printf("first child exit\n");
			exit(0);
		}
		wait(&status);
	}
	new_argv = ft_split(argv[len - 1], ' ');
	execute_command(new_argv, env);
	clean_arg(0, 0, &new_argv, 0);
	return (1);
}
