/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:03:54 by jinwkim           #+#    #+#             */
/*   Updated: 2020/04/12 00:28:23 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

typedef struct	s_info
{
	char		*old;
	char		*buf;
	int			len;
	int			index;
	int			ret;
	int			val;
}				t_info;

int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *str);
void			*ft_calloc(size_t num, size_t size);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *str, unsigned int start, size_t len);
#endif
