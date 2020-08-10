/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 05:33:44 by jinwkim           #+#    #+#             */
/*   Updated: 2020/08/10 16:52:26 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_environ.h"
#include "libft.h"
#include "error.h"

#define INVALID_MSG "not valid in this context"

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

int			ft_export(int argc, char **argv, char ***env)
{
	int		idx;
	char	*key;
	char	*value;

	idx = 0;
	if (argc == 1)
		return (export_no_arg(argv[0], *env));
	while (idx < argc)
	{
		key = 0;
		value = 0;
		if (check_key_value(argv[idx]) == 1)
		{
			set_key(argv[idx], &key);
			set_value(argv[idx], &value);
			if (check_validate(key) == 0)
				return (error_msg_param(argv[0], INVALID_MSG, key));
			else if (check_key(env, key, value) == 0)
				return (error_msg(argv[0], "error"));
		}
		clean_arg(&key, &value, 0, 0);
		idx++;
	}
	return (EXIT_SUCCESS);
}

void		ft_export_one(char *key, char *value, char **env)
{
	int		size;
	char	*buf;
	char	**argv;

	argv = (char**)malloc(sizeof(char*) * 3);
	argv[0] = "export";
	argv[2] = NULL;
	size = ft_strlen(key) + ft_strlen("=") + ft_strlen(value) + 1;
	buf = (char*)malloc(sizeof(char) * size);
	ft_memset(buf, 0, size);
	ft_strlcat(buf, key, size);
	ft_strlcat(buf, "=", size);
	ft_strlcat(buf, value, size);
	argv[1] = buf;
	ft_export(2, argv, &env);
	free(buf);
	free(argv);
}
