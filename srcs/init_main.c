/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 19:50:09 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/15 20:20:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ft_environ.h"
#include "error.h"

char	*make_prompt(char **env)
{
	char	*result;
	char	*sub;

	result = 0;
	sub = get_env_value(env, "USER");
	if (sub != 0)
		result = ft_strjoin(sub, "% ");
	else
		result = sub;
	return (result);
}

int		init_main(char **prompt, char **environ, char ***env)
{
	int		len;

	len = get_strarr_size(environ);
	if ((*prompt = make_prompt(environ)) == 0)
	{
		if ((*prompt = ft_strdup("user% ")) == 0)
			return (0);
	}
	if ((*env = cpy_env(environ, len)) == 0)
	{
		if (*prompt != 0)
		{
			free(*prompt);
			*prompt = 0;
		}
		return (0);
	}
	return (1);
}
