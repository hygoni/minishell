/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:11:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/10 21:15:02 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ft_environ.h"

extern	int		g_status;

char	*parse_path_sub_key(int *idx, char *arg)
{
	int		i;
	char	*key;

	key = ft_strdup("");
	i = *idx;
	if (arg[i] == '?')
	{
		i++;
		if ((key = ft_strdup("?")) == NULL)
			return (NULL);
	}
	else
	{
		while (arg[i] != '$' && arg[i] != '\0'
				&& (arg[i] == '_' || ft_isalnum(arg[i])))
		{
			if ((key = ft_strjoinc(key, arg[i++])) == NULL)
				return (NULL);
		}
	}
	*idx = i;
	return (key);
}

char	*parse_path_sub(int *idx, char *arg, char ***env)
{
	int		i;
	char	*token;
	char	*key;

	i = *idx;
	i++;
	if ((key = parse_path_sub_key(&i, arg)) == NULL)
		return (NULL);
	token = get_env_value(*env, key);
	if (ft_strcmp(key, "?") == 0)
	{
		token = ft_itoa(((g_status >> 8) & 255));
	}
	else
		token = (token == NULL) ? ft_strdup("") : ft_strdup(token);
	*idx = i;
	free(key);
	return (token);
}

char	*parse_path_token(int *idx, char *arg, char ***env)
{
	char	*token;
	int		i;

	i = *idx;
	if (arg[i] == '$')
	{
		if ((token = parse_path_sub(&i, arg, env)) == NULL)
			return (NULL);
	}
	else
	{
		token = ft_strdup("");
		while (arg[i] != '$' && arg[i] != '\0')
		{
			if (token == NULL)
				return (NULL);
			token = ft_strjoinc(token, arg[i++]);
		}
	}
	*idx = i;
	return (token);
}

char	*parse_path(char *arg, char ***env)
{
	int		i;
	char	*parsed;
	char	*token;
	char	*to_free;

	if ((parsed = ft_strdup("")) == NULL)
		return (NULL);
	i = 0;
	while (arg[i] != '\0')
	{
		token = parse_path_token(&i, arg, env);
		to_free = parsed;
		parsed = ft_strjoin(parsed, token);
		free(token);
		free(to_free);
	}
	free(arg);
	return (parsed);
}
