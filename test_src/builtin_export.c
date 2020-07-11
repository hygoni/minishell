/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 05:33:44 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/12 05:34:00 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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

char	*get_key(char *str)
{
	char	*result;
	int		end;

	end = 0;
	while (str[end] != '=')
		end++;
	result = ft_substr(str, 0, end);
	return (result);
}

char	*get_value(char *str)
{
	char	*result;
	int		start;
	int		len;

	start = 0;
	while (str[start] != '=')
		start++;
	start++;
	len = ft_strlen(str);
	result = ft_substr(str, start, len - start);
	return (result);
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
			key = get_key(argv[idx]);
			value = get_value(argv[idx]);
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
