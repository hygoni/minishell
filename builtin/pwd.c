/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:45:34 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/14 16:04:11 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include "constant.h"
#include "libft.h"
#include "ft_environ.h"
#include "error.h"

#define TOO_MANY_ARGUMENTS		"too many arguments"
#define BAD_OPTION				"bad option"
#define EXE_NAME				"pwd"
#define PWD						"PWD"

int		option(char *argument, int *is_physical, char *param)
{
	param[0] = '-';
	param[2] = '\0';
	argument++;
	while (*argument != '\0')
	{
		param[1] = *argument;
		if (*argument == 'L')
			*is_physical = (*is_physical) ? TRUE : FALSE;
		else if (*argument == 'P')
			*is_physical = TRUE;
		else
			return (FALSE);
		argument++;
	}
	return (TRUE);
}

int		pwd(int argc, char **argv, char **environ)
{
	int		i;
	int		is_physical;
	char	buf[PATH_MAX + 1];
	char	param[3];

	is_physical = FALSE;
	i = 1;
	while (i < argc)
	{
		if (*(argv[i]) != '-')
			return (error_msg(EXE_NAME, TOO_MANY_ARGUMENTS));
		else if (option(argv[i], &is_physical, param) == FALSE)
			return (error_msg_param(EXE_NAME, BAD_OPTION, param));
		i++;
	}
	if (is_physical)
	{
		getcwd(buf, PATH_MAX);
		ft_putstr_endl(buf);
	}
	else
		ft_putstr_endl(get_env_value(environ, PWD));
	return (EXIT_SUCCESS);
}
