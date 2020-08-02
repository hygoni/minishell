/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 14:50:57 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/02 15:02:51 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "libft.h"
#include "error.h"
#include "signals.h"

#define EXE_NAME	"minishell"

extern pid_t	g_child;
extern int		g_status;
extern int		g_interrupted;
extern char		*g_prompt;
extern char		*g_process_name;

void	sigint(int signal)
{
	g_interrupted = 1;
	g_status = 130;
	ft_putchar(8);
	ft_putchar(8);
	ft_putchar('\n');
	if (g_child != 0)
		kill(g_child, signal);
	error_msg_param(EXE_NAME, g_process_name, "sigint");
	if (ft_strcmp(EXE_NAME, g_process_name) == 0)
		write(1, g_prompt, ft_strlen(g_prompt));
}

void	sigquit(int signal)
{
	g_interrupted = 1;
	g_status = 131;
	ft_putchar(8);
	ft_putchar(8);
	ft_putchar('\n');
	if (g_child != 0)
		kill(g_child, signal);
	error_msg_param(EXE_NAME, g_process_name, "sigquit");
	if (ft_strcmp(EXE_NAME, g_process_name) == 0)
		write(1, g_prompt, ft_strlen(g_prompt));
}
