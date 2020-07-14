/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:45:46 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/12 16:47:44 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		error_msg(char *name, char *msg)
{
	ft_putstr(name);
	ft_putstr(": ");
	ft_putstr_endl(msg);
	return (EXIT_FAILURE);
}

int		error_msg_param(char *name, char *msg, char *param)
{
	ft_putstr(name);
	ft_putstr(": ");
	ft_putstr(msg);
	ft_putstr(": ");
	ft_putstr_endl(param);
	return (EXIT_FAILURE);
}
