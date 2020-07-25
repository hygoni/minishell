/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:45:46 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/25 16:17:45 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#define STDERR 2

int		error_msg(char *name, char *msg)
{
	ft_putstr_fd(name, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_endl_fd(msg, STDERR);
	return (EXIT_FAILURE);
}

int		error_msg_param(char *name, char *msg, char *param)
{
	ft_putstr_fd(name, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_endl_fd(param, STDERR);
	return (EXIT_FAILURE);
}

int		error_msg_parse(char *param)
{
	ft_putstr_fd("minishell", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd("parse error near '", STDERR);
	ft_putstr_fd(param, STDERR);
	ft_putstr_endl_fd("'", STDERR);
	return (EXIT_FAILURE);
}
