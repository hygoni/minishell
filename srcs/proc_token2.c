/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_token2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:17:28 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/03 14:36:57 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

char	*proc_str(int *idx, char *arg, char *str, char ***env)
{
	int		i;
	char	*tmp;
	char	*to_free;
	char	*parsed;

	i = *idx;
	if ((tmp = ft_strdup("")) == NULL)
		return (NULL);
	while (arg[i] != '|' && arg[i] != ';' && arg[i] != ' ' && arg[i] != '\''
			&& arg[i] != '"' && arg[i] != '\0' && arg[i] != '*')
	{
		if (arg[i] == '\\')
			i++;
		if ((tmp = ft_strjoinc(tmp, arg[i++])) == NULL)
			return (NULL);
	}
	if ((parsed = parse_path(tmp, env)) == NULL)
		return (NULL);
	to_free = str;
	str = ft_strjoin(str, parsed);
	free(to_free);
	free(parsed);
	*idx = i;
	return (str);
}

char	*proc_wildcard(int *idx, char *str, char ***argv)
{
	int				i;
	char			*to_free;
	DIR				*dir;
	struct dirent	*dirent;

	i = *idx;
	i++;
	if (ft_strlen(str) > 0)
		*argv = extend_argv(*argv, str);
	else
		free(str);
	str = ft_strdup("");
	if ((dir = opendir(".")) == NULL)
		return (NULL);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (*(dirent->d_name) != '.')
			*argv = extend_argv(*argv, ft_strdup(dirent->d_name));
	}
	closedir(dir);
	to_free = str;
	*idx = i;
	return (str);
}
