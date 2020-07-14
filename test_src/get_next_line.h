/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:03:54 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/14 19:22:39 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include "libft.h"

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
#endif
