/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 05:33:44 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/15 15:27:10 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_environ.h"
#include "libft.h"
#include "error.h"

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

void		_export(int argc, char **argv, char ***env)
{
	int		idx;
	char	*key;
	char	*value;

	idx = 0;
	while (idx < argc)
	{
		key = 0;
		value = 0;
		if (check_key_value(argv[idx]) == 1)
		{
			set_key(argv[idx], &key);
			set_value(argv[idx], &value);
			if (check_validate(key) == 0)
				error_msg_param(argv[0], "not valid in this context", key);
			else if (check_key(env, key, value) == 0)
				error_msg(argv[0], "error");
		}
		if (key != 0 && *key != 0)
			free(key);
		if (value != 0 && *value != 0)
			free(value);
		idx++;
	}
}

void		_export_one(char *key, char *value, char **env)
{
	int		size;
	char	*buf;
	char	**argv;

	argv = (char**)malloc(sizeof(char*) * 2);
	argv[1] = NULL;
	size = ft_strlen(key) + ft_strlen("=") + ft_strlen(value) + 1;
	buf = (char*)malloc(sizeof(char) * size);
	ft_memset(buf, 0, size);
	ft_strlcat(buf, key, size);
	ft_strlcat(buf, "=", size);
	ft_strlcat(buf, value, size);
	argv[0] = buf;
	_export(1, argv, &env);
	free(buf);
	free(argv);
}
