/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:51:00 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/13 23:51:17 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_environ.h"
#include "libft.h"
#include <stdio.h>

char	**realloc_env(char **env, int size)
{
	char	**result;
	int		idx;
	int		len;
	int		str_len;

	idx = get_strarr_size(env);
	len = (idx > size ? size : idx);
	if ((result = (char **)malloc(sizeof(char *) * (size + 1))) == 0)
		return (0);
	idx = 0;
	while (idx < len)
	{
		str_len = ft_strlen(env[idx]) + 1;
		if ((result[idx] =
					(char *)malloc(sizeof(char) * str_len)) == 0)
			return (clean_env(result, idx));
		ft_strlcpy(result[idx], env[idx], str_len);
		idx++;
	}
	result[size] = 0;
	return (result);
}
