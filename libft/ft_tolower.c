/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <9hrack@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:46:11 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/02/24 19:46:45 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
	{
		return (c - 'A' + 'a');
	}
	else
	{
		return (c);
	}
}
