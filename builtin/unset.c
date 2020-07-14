/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:02:25 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/14 20:08:08 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_environ.h"
#include <stdio.h>

int			check_validate(char *str)
{
	int		idx;

	idx = 0;
	if ((str[0] != 0) && (ft_isdigit((int)str[0]) == 1))
	{
		ft_putendl_fd("not valid key", 2);
		return (0);
	}
	while (str[idx] != 0)
	{
		if ((ft_isalnum((int)str[idx]) == 0) && (str[idx] != '_'))
			return (0);
		idx++;
	}
	return (1);
}

int			find_remove_key(char **env, char *key)
{
	int		idx;

	idx = 0;
	while (env[idx] != 0)
	{
		if (ft_strncmp(env[idx], key, get_equal_idx(env[idx])) == 0)
			return (idx);
		idx++;
	}
	return (-1);
}

void		env_arr_move(char **env, int idx, int len)
{
	while (idx < len && env[idx] != 0)
	{
		env[idx] = env[idx + 1];
		idx++;
	}
}

void		builtin_unset(int argc, char **argv, char ***env)
{
	int		idx;
	int		remove_idx;
	int		arr_size;
	char	**new_env;

	idx = 0;
	while (idx < argc)
	{
		arr_size = get_strarr_size(*env);
		if (check_validate(argv[idx]) == 1)
		{
			if ((remove_idx = find_remove_key(*env, argv[idx])) != -1)
			{
				free((*env)[remove_idx]);
				env_arr_move(*env, remove_idx, arr_size);
				if ((new_env = realloc_env(*env, arr_size - 1)) == 0)
					clean_arg(0, 0, argv, *env);
				*env = clean_env(*env, arr_size);
				*env = new_env;
			}
		}
		idx++;
	}
}
