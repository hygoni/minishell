/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 23:52:30 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/15 20:51:18 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		ft_env(char **env)
{
	int		idx;

	idx = 0;
	while (env[idx] != 0)
	{
		ft_putendl_fd(env[idx], 1);
		idx++;
	}
	return (EXIT_SUCCESS);
}
