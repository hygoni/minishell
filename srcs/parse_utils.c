/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:18:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/02 16:28:23 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		find(char **argv, char *find)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (!ft_strcmp(argv[i], find))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoinc(char *str, char c)
{
	int		len;
	char	*new;

	len = ft_strlen(str) + 1;
	new = malloc(sizeof(char) * (len + 1));
	ft_strcpy(new, str);
	new[len - 1] = c;
	new[len] = '\0';
	free(str);
	return (new);
}

char	**extend_argv(char **argv, char *str)
{
	int		len;
	char	**new;
	int		i;

	len = 0;
	while (argv[len] != NULL)
		len++;
	new = malloc(sizeof(char*) * (len + 2));
	i = 0;
	while (i < len)
	{
		new[i] = argv[i];
		i++;
	}
	new[i++] = str;
	new[i] = NULL;
	free(argv);
	return (new);
}

char	***extend_argv_3d(char ***argv, char **str)
{
	int		len;
	char	***new;
	int		i;

	len = 0;
	while (argv[len] != NULL)
		len++;
	new = malloc(sizeof(char**) * (len + 2));
	i = 0;
	while (i < len)
	{
		new[i] = argv[i];
		i++;
	}
	new[i++] = str;
	new[i] = NULL;
	free(argv);
	return (new);
}
