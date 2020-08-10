/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:15:30 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/10 20:19:34 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "error.h"

extern int g_status;

void	ft_exit(char **argv, int size)
{
	int		i;
	char	*status;

	if (size == 1)
		exit(EXIT_SUCCESS);
	status = argv[1];
	if (size > 2)
	{
		error_msg("exit", "too many arguments");
		return ;
	}
	i = 0;
	while (status[i] != '\0')
	{
		if (status[i] < '0' || status[i] > '9')
		{
			error_msg_param("exit", status, "numeric argument required");
			break ;
		}
		i++;
	}
	g_status = (status == NULL) ? 0 : ft_atoi(status);
	exit(g_status);
}
