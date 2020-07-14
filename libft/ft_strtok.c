/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 18:14:14 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/14 14:37:49 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char *p = NULL;

	if (str != NULL)
		p = str;
	else if (p == NULL)
		return (NULL);
	str = p + ft_strspn(p, delim);
	p = str + ft_strcspn(str, delim);
	if (p == str)
		return (p = NULL);
	if (*p)
	{
		*p = '\0';
		p++;
	}
	else
		p = NULL;
	return (str);
}
