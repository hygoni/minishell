/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 21:08:56 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/29 19:22:36 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_2d(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_2d_len(char **argv, int len)
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
}

void	free_3d(char ***argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free_2d(argv[i]);
		i++;
	}
	free(argv);
}
