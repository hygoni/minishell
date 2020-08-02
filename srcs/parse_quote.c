/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:12:38 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/02 16:27:17 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "error.h"
#include <stdlib.h>

#define EXE_NAME "minishell"
#define MSG_DOUBLE_QUOTE_NOT_CLOSED "double quote isn't closed"
#define MSG_SINGLE_QUOTE_NOT_CLOSED "single quote isn't closed"

char	*proc_single_quote_sub(int *save, int *idx, char *arg)
{
	char	*tmp;
	int		i;

	i = *idx;
	i++;
	if ((tmp = ft_strdup("")) == NULL)
		return (NULL);
	while (arg[i] != '\'' && arg[i] != '\0')
	{
		if (arg[i] == '\\')
		{
			i++;
			if (arg[i] != '\'' && arg[i] != '\\')
				tmp = ft_strjoinc(tmp, '\\');
			tmp = ft_strjoinc(tmp, arg[i++]);
			if (tmp == NULL)
				return (NULL);
		}
		else if ((tmp = ft_strjoinc(tmp, arg[i++])) == NULL)
			return (NULL);
	}
	*save = i;
	return (tmp);
}

char	*proc_single_quote(int *idx, char *arg, char *str)
{
	char	*tmp;
	int		i;
	char	*to_free;

	if ((tmp = proc_single_quote_sub(&i, idx, arg)) == NULL)
		return (NULL);
	to_free = str;
	str = ft_strjoin(str, tmp);
	free(to_free);
	free(tmp);
	if (arg[i] == '\'')
		i++;
	else
	{
		error_msg(EXE_NAME, MSG_SINGLE_QUOTE_NOT_CLOSED);
		return (NULL);
	}
	*idx = i;
	return (str);
}

char	*proc_double_quote_sub(int *save, int *idx, char *arg)
{
	int		i;
	char	*tmp;

	i = *idx;
	i++;
	if ((tmp = ft_strdup("")) == NULL)
		return (NULL);
	while (arg[i] != '"' && arg[i] != '\0')
	{
		if (arg[i] == '\\')
		{
			i++;
			if (arg[i] != '\"' && arg[i] != '\\')
				tmp = ft_strjoinc(tmp, '\\');
			if ((tmp = ft_strjoinc(tmp, arg[i++])) == NULL)
				return (NULL);
		}
		else if ((tmp = ft_strjoinc(tmp, arg[i++])) == NULL)
			return (NULL);
	}
	*save = i;
	return (tmp);
}

char	*proc_double_quote(int *idx, char *arg, char *str, char ***env)
{
	int		i;
	char	*tmp;
	char	*to_free;
	char	*parsed;

	if ((tmp = proc_double_quote_sub(&i, idx, arg)) == NULL)
		return (NULL);
	if (arg[i] == '"')
		i++;
	else
	{
		error_msg(EXE_NAME, MSG_DOUBLE_QUOTE_NOT_CLOSED);
		return (NULL);
	}
	to_free = str;
	if ((parsed = parse_path(tmp, env)) == NULL)
		return (NULL);
	if ((str = ft_strjoin(str, parsed)) == NULL)
		return (NULL);
	free(to_free);
	free(parsed);
	*idx = i;
	return (str);
}
