/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <9hrack@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:45:08 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/02/24 19:45:57 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
	{
		return (c - 'a' + 'A');
	}
	else
	{
		return (c);
	}
}
