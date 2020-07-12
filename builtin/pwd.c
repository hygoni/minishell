/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:45:34 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/12 16:07:42 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include "constant.h"
#include "libft.h"
#include "ft_environ.h"

#define TOO_MANY_ARGUMENTS		"too many arguments"
#define BAD_OPTION				"bad option"
#define EXE_NAME				"pwd"
#define PWD						"PWD"

void	error_too_many_arguments(void)
{
	ft_putstr(EXE_NAME);
	ft_putstr(": ");
	ft_putstr(TOO_MANY_ARGUMENTS);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

void	error_bad_option(char param)
{
	ft_putstr(EXE_NAME);
	ft_putstr(": ");
	ft_putstr(BAD_OPTION);
	ft_putstr(": -");
	ft_putchar(param);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

int		option(char *argument)
{
	int		is_physical;

	is_physical = FALSE;
	argument++;
	while (*argument != '\0')
	{
		if (*argument == 'L')
			is_physical = (is_physical) ? TRUE : FALSE;
		else if (*argument == 'P')
			is_physical = TRUE;
		else
			error_bad_option(*argument);
		argument++;
	}
	return (is_physical);
}

void	pwd(int argc, char **argv, char **environ)
{
	int		i;
	int		is_physical;
	char	buf[PATH_MAX + 1];

	is_physical = FALSE;
	i = 1;
	while (i < argc)
	{
		if (*(argv[i]) != '-')
			error_too_many_arguments();
		else
			is_physical = is_physical | option(argv[i]);
		i++;
	}
	if (is_physical)
	{
		getcwd(buf, PATH_MAX);
		ft_putstr_endl(buf);
	}
	else
	{
		ft_putstr_endl(get_env_value(environ, PWD));
	}
}
