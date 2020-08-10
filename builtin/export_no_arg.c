/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:44:40 by jinwkim           #+#    #+#             */
/*   Updated: 2020/08/10 17:40:54 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_environ.h"
#include "error.h"
#include <unistd.h>
#include <stdlib.h>

static char		*clean_sub(char *sub, char *sub2, char **env)
{
	int		len;
	int		idx;

	if (sub != 0)
		free(sub);
	if (sub2 != 0)
		free(sub2);
	if (env != 0)
	{
		idx = 0;
		len = get_strarr_size(env);
		while (idx < len)
		{
			free(env[idx]);
			idx++;
		}
		free(env);
	}
	return (0);
}

char			*key_value_quotes(char *key, char *value)
{
	char	*sub;
	char	*result;

	if ((sub = ft_strjoin("\"", value)) == 0)
		return (0);
	if ((result = ft_strjoin(sub, "\"")) == 0)
		return (clean_sub(sub, 0, 0));
	free(sub);
	sub = result;
	if ((result = ft_strjoin("=", sub)) == 0)
		return (clean_sub(sub, 0, 0));
	free(sub);
	sub = result;
	if ((result = ft_strjoin(key, sub)) == 0)
		return (clean_sub(sub, 0, 0));
	free(sub);
	sub = result;
	if ((result = ft_strjoin("declare -x ", sub)) == 0)
		return (clean_sub(sub, 0, 0));
	free(sub);
	return (result);
}

void			swap_value(char *key1, char *key2, char **env1, char **env2)
{
	char	*tmp;

	if (ft_strcmp(key1, key2) > 0)
	{
		tmp = *env2;
		*env2 = *env1;
		*env1 = tmp;
	}
}

void			sorting_env(char **env)
{
	int		idx;
	int		limit;
	char	*key1;
	char	*key2;

	limit = get_strarr_size(env);
	while (limit >= 0)
	{
		idx = 0;
		while (idx + 1 < limit)
		{
			set_key(env[idx], &key1);
			set_key(env[idx + 1], &key2);
			swap_value(key1, key2, &(env[idx]), &(env[idx + 1]));
			clean_sub(key1, key2, 0);
			idx++;
		}
		limit--;
	}
}

int				export_no_arg(char *name, char **env)
{
	int		idx;
	char	*key;
	char	*value;
	char	*result;
	char	**sort_env;

	idx = get_strarr_size(env);
	sort_env = cpy_env(env, idx);
	sorting_env(sort_env);
	idx = 0;
	while (sort_env[idx] != 0)
	{
		set_key(sort_env[idx], &key);
		set_value(sort_env[idx++], &value);
		if ((result = key_value_quotes(key, value)) == 0)
		{
			clean_sub(key, value, sort_env);
			return (error_msg(name, "error"));
		}
		ft_putstr_endl(result);
		free(result);
		clean_sub(key, value, 0);
	}
	clean_sub(0, 0, sort_env);
	return (EXIT_SUCCESS);
}
