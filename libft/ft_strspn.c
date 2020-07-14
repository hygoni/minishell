/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 18:18:55 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/14 14:37:24 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strspn(const char *s1, const char *s2)
{
	size_t	ret;

	ret = 0;
	while (*s1 && ft_strchr(s2, *s1++))
		ret++;
	return (ret);
}
