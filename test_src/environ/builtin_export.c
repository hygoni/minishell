/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 05:33:44 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/13 23:46:55 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_environ.h"
#include "libft.h"

int			add_env(char ***env, char *key, char *value)
{
	char	*result;
	char	*sub;
	int		len;
	char	**new_env;

	len = get_strarr_size(*env);
	if ((new_env = realloc_env(*env, len + 1)) == 0)
		return (0);
	if ((sub = ft_strjoin(key, "=")) == 0)
	{
		clean_env(new_env, len);
		return (0);
	}
	if ((result = ft_strjoin(sub, value)) == 0)
	{
		free(sub);
		clean_env(new_env, len);
		return (0);
	}
	new_env[len] = result;
	*env = clean_env(*env, len);
	*env = new_env;
	return (1);
}

int			check_key_value(char *str)
{
	int		idx;

	idx = 0;
	while (str[idx] != 0 && str[idx] != '=')
		idx++;
	if (idx == 0 || str[idx] == 0)
		return (0);
	else
		return (1);
}

int			set_key(char *str, char **key)
{
	int		end;

	end = get_equal_idx(str);
	if ((*key = ft_substr(str, 0, end)) == 0)
		return (0);
	return (1);
}

int			set_value(char *str, char **value)
{
	int		start;
	int		len;

	start = get_equal_idx(str);
	start++;
	len = ft_strlen(str);
	if ((*value = ft_substr(str, start, len - start)) == 0)
		return (0);
	return (1);
}

void		builtin_export(int argc, char **argv, char ***env)
{
	int		idx;
	char	*key;
	char	*value;

	idx = 0;
	while (idx < argc)
	{
		if (check_key_value(argv[idx]) == 1)
		{
			if (set_key(argv[idx], &key) == 0)
				clean_arg(0, 0, argv, *env);
			if (check_validate(key) == 0)
				clean_arg(0, 0, argv, *env);
			if (set_value(argv[idx], &value) == 0)
				clean_arg(key, 0, argv, *env);
			if (check_key(env, key, value) == 0)
				clean_arg(key, value, argv, *env);
			if (*key != 0)
				free(key);
			if (*value != 0)
				free(value);
		}
		idx++;
	}
}
