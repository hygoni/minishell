/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 21:08:56 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/13 21:43:50 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		free_2d(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	return (1);
}

int		free_2d_len(char **argv, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (argv[i] != NULL)
			free(argv[i]);
		i++;
	}
	free(argv);
	return (1);
}

int		free_3d(char ***argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free_2d(argv[i]);
		i++;
	}
	free(argv);
	return (1);
}
