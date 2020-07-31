/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:15:30 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/15 20:59:43 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "error.h"

extern int g_status;

void	ft_exit(char *status)
{
	if (status != 0)
		g_status = ft_atoi(status);
	else
		g_status = 0;
	exit(g_status);
}
