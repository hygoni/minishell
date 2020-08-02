/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_token2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:17:28 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/02 16:32:37 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

char	*proc_str(int *idx, char *arg, char *str, char ***env)
{
	int		i;
	char	*tmp;
	char	*to_free;
	char	*parsed;

	i = *idx;
	if ((tmp = ft_strdup("")) == NULL)
		return (NULL);
	while (arg[i] != '|' && arg[i] != ';' && arg[i] != ' '
			&& arg[i] != '\'' && arg[i] != '"' && arg[i] != '\0')
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
