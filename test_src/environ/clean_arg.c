/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:04:44 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/13 23:47:42 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_environ.h"

void			free_string_arr(char **arg)
{
	int		idx;
	int		len;

	len = get_strarr_size(arg);
	idx = 0;
	while (idx < len)
	{
		free(arg[idx]);
		idx++;
	}
	free(arg);
}

void			clean_arg(char *key, char *value, char **arg, char **env)
{
	if (key != 0)
		free(key);
	if (value != 0)
		free(value);
	if (arg != 0)
		free_string_arr(arg);
	if (env != 0)
		free_string_arr(arg);
	exit(1);
}
