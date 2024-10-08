/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 14:36:15 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/26 15:55:16 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int	ft_echo(int argc, char **argv)
{
	int		enter;
	int		i;

	enter = TRUE;
	i = 1;
	if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
	{
		i = 2;
		enter = FALSE;
	}
	while (i < argc)
	{
		ft_putstr(argv[i]);
		if (i != argc - 1)
			ft_putchar(' ');
		i++;
	}
	if (enter)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}
