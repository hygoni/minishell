/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 05:36:16 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/12 15:40:57 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

extern	char **environ;

int		get_strarr_size(char **arr)
{
	int		len;

	len = 0;
	while (arr[len] != 0)
		len++;
	return (len);
}

char	**clean_env(char **env, int size)
{
	int		idx;

	idx = 0;
	while (idx < size)
	{
		free(env[idx]);
		idx++;
	}
	free(env);
	return (0);
}

char	**cpy_env(char **environ, int len)
{
	char	**result;
	int		idx;
	int		size;

	if ((result = (char **)malloc(sizeof(char *) * len)) == 0)
		return (0);
	idx = 0;
	while (idx < len)
	{
		size = ft_strlen(environ[idx]) + 1;
		if ((result[idx] =
			(char *)malloc(sizeof(char) * size)) == 0)
			return (clean_env(result, idx));
		ft_strlcpy(result[idx], environ[idx], size);
		idx++;
	}
	result[idx] = 0;
	return (result);
}
