/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:45:34 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/15 20:00:25 by jinwkim          ###   ########.fr       */
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
#define EXE_NAME				"pwd"
#define PWD						"PWD"
#define ENV_ERROR				"environment variables error"

int		ft_pwd(int argc, char **environ)
{
	char	*logical;

	if (argc != 1)
		return (error_msg(EXE_NAME, TOO_MANY_ARGUMENTS));
	if ((logical = get_env_value(environ, PWD)) == NULL)
		return (error_msg(EXE_NAME, ENV_ERROR));
	ft_putstr_endl(logical);
	return (EXIT_SUCCESS);
}
