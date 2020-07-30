/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:28:16 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/30 17:07:05 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BEEP 7
#define BACKSPACE 8
#define ESCAPE 33

char escape(char c)
{
	if (c == 'n')
		return ('\n');
	else if (c == 'a')
		return (BEEP);
	else if (c == 'b')
		return (BACKSPACE);
	else if (c == 'e')
		return (ESCAPE);
	else if (c == 'f')
		return ('\f');
	else if (c == 't')
		return ('\t');
	else if (c == 'v')
		return ('\v');
	else
		return (c);
}
