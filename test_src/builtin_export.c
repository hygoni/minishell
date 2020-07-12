/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 05:33:44 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/12 15:39:02 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_environ.h"
#include "libft.h"

int		add_env(char *key, char *value)
{
	char	*result;
	char	*sub;

	sub = ft_strjoin(key, "=");
	result = ft_strjoin(sub, value);
	free(sub);
	return (1);
}

int		check_key_value(char *str)
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

int		set_key(char *str, char **key)
{
	int		end;

	end = 0;
	while (str[end] != '=')
		end++;
	if ((*key = ft_substr(str, 0, end)) == 0)
		return (0);
	return (1);
}

int		set_value(char *str, char **value)
{
	int		start;
	int		len;

	start = 0;
	while (str[start] != '=')
		start++;
	start++;
	len = ft_strlen(str);
	if ((*value = ft_substr(str, start, len - start)) == 0)
		return (0);
	return (1);
}

void	builtin_export(int argc, char **argv)
{
	int		idx;
	char	*key;
	char	*value;

	idx = 0;
	while (idx < argc)
	{
		if (check_key_value(argv[idx]) == 1)
		{
			if (get_key(argv[idx], &key) == 0)
				exit(1);
			if (get_value(argv[idx]) == 0)
			{
				free(key);
				exit(1);
			}
			if (add_env(key, value) == 0)
				write(2, "error\n", 6);
			if (*key != 0)
				free(key);
			if (*value != 0)
				free(value);
		}
		idx++;
	}
}
