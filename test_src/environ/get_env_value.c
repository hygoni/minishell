/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 05:36:26 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/13 23:50:19 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		get_equal_idx(char *str)
{
	int		idx;

	idx = 0;
	while (str[idx] != 0)
	{
		if (str[idx] == '=')
			return (idx);
		idx++;
	}
	return (0);
}

/*
** description:	get value in environ variable
** param:
** 	char **env:	environ variable
** 	char *key:	key
** return:		value
*/

char	*get_env_value(char **env, char *key)
{
	char	*result;
	int		equal;

	while (*env != 0)
	{
		equal = get_equal_idx(*env);
		if (ft_strncmp(*env, key, equal) == 0)
		{
			result = ft_strchr(*env, '=');
			result++;
			return (result);
		}
		env++;
	}
	return (0);
}
