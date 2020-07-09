/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:03:45 by jinwkim           #+#    #+#             */
/*   Updated: 2020/03/06 23:58:03 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	result;

	result = 0;
	while (*str != 0)
	{
		str++;
		result++;
	}
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	size_t			size;
	unsigned int	index;

	index = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	if ((result = (char *)ft_calloc(size + 1, sizeof(char))) == 0)
		return (0);
	result[size] = 0;
	while (*s1 != 0)
	{
		result[index] = *s1;
		s1++;
		index++;
	}
	while (*s2 != 0)
	{
		result[index] = *s2;
		s2++;
		index++;
	}
	return (result);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*result;
	char	*start;
	size_t	index;

	index = num * size;
	if ((result = malloc(size * num)) == 0)
		return (0);
	start = (char *)result;
	while (index > 0)
	{
		*start = 0;
		start++;
		index--;
	}
	return (result);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	index;

	index = 0;
	while ((index < n) && (*src != 0))
	{
		dest[index] = *src;
		src++;
		index++;
	}
	while (index < n)
	{
		dest[index] = 0;
		index++;
	}
	return (dest);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	result_len;
	char	*result;

	str_len = ft_strlen(str);
	if (str_len > start)
	{
		result_len = (str_len - start) >= len ? len : (str_len - start);
		if ((result = (char *)ft_calloc(result_len + 1, sizeof(char))) == 0)
			return (0);
		result = ft_strncpy(result, str + start, result_len);
	}
	else
	{
		if ((result = (char *)ft_calloc(1, sizeof(char))) == 0)
			return (0);
	}
	return (result);
}
