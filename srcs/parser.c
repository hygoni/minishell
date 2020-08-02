/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:32:05 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/02 16:27:40 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute_command.h"
#include "free.h"
#include "ft_environ.h"
#include "builtin.h"
#include "error.h"
#include "parser.h"
#include <stdlib.h>
#define EXE_NAME "minishell"
#define MSG_DOUBLE_QUOTE_NOT_CLOSED "double quote isn't closed"
#define MSG_SINGLE_QUOTE_NOT_CLOSED "single quote isn't closed"

extern int g_status;

void	parse_pipes(char **argv2, char ***env)
{
	char	***argv3;
	int		i;
	int		len;
	char	**add;

	len = 0;
	while (argv2[len] != NULL)
		len++;
	argv3 = (char***)ft_calloc(sizeof(char**), 1);
	add = (char**)ft_calloc(sizeof(char*), 1);
	i = 0;
	while (i < len)
	{
		if (!ft_strcmp(argv2[i], "|"))
		{
			argv3 = extend_argv_3d(argv3, add);
			add = (char**)ft_calloc(sizeof(char*), 1);
		}
		else
			add = extend_argv(add, ft_strdup(argv2[i]));
		i++;
	}
	argv3 = extend_argv_3d(argv3, add);
	execute_commands(argv3, env);
	free_3d(argv3);
}

void	parse_commands_sub(char **argv, char ***env, int end, int len)
{
	int		start;

	start = 0;
	while (end >= 0 && start < len)
	{
		if (argv[end] != NULL)
			free(argv[end]);
		argv[end] = NULL;
		parse_pipes(&argv[start], env);
		start = end + 1;
		end = find(&argv[start], ";");
		if (end >= 0)
			end += start;
	}
	if (argv[start] != NULL && ft_strcmp(argv[start], ";") != 0)
		parse_pipes(&argv[start], env);
}

void	parse_commands(char *cmd_line, char ***env)
{
	int		end;
	int		start;
	char	**argv;
	int		len;

	len = 0;
	if (ft_strlen(cmd_line) == 0)
		return ;
	else if ((argv = proc_quote_path(cmd_line, env)) == NULL)
		return ;
	end = find(argv, ";");
	start = 0;
	while (argv[len] != NULL)
		len++;
	parse_commands_sub(argv, env, end, len);
	free_2d_len(argv, len);
}
