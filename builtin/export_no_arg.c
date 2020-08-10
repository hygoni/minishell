/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:44:40 by jinwkim           #+#    #+#             */
/*   Updated: 2020/08/10 16:58:33 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_environ.h"
#include "error.h"
#include <unistd.h>
#include <stdlib.h>

static char		*clean_sub(char *sub, char *sub2)
{
	if (sub != 0)
		free(sub);
	if (sub2 != 0)
		free(sub2);
	return (0);
}

char			*key_value_quotes(char *key, char *value)
{
	char	*sub;
	char	*result;

	if ((sub = ft_strjoin("\"", value)) == 0)
		return (0);
	if ((result = ft_strjoin(sub, "\"")) == 0)
		return (clean_sub(sub, 0));
	free(sub);
	sub = result;
	if ((result = ft_strjoin("=", sub)) == 0)
		return (clean_sub(sub, 0));
	free(sub);
	sub = result;
	if ((result = ft_strjoin(key, sub)) == 0)
		return (clean_sub(sub, 0));
	free(sub);
	sub = result;
	if ((result = ft_strjoin("declare -x ", sub)) == 0)
		return (clean_sub(sub, 0));
	return (result);
}

int				export_no_arg(char *name, char **env)
{
	int		idx;
	char	*key;
	char	*value;
	char	*result;

	idx = 0;
	while (env[idx] != 0)
	{
		set_key(env[idx], &key);
		set_value(env[idx], &value);
		if ((result = key_value_quotes(key, value)) == 0)
		{
			clean_sub(key, value);
			return (error_msg(name, "error"));
		}
		ft_putstr_endl(result);
		free(result);
		clean_sub(key, value);
		idx++;
	}
	return (EXIT_SUCCESS);
}
