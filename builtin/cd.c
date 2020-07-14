/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:26:13 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/12 16:57:18 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_environ.h"
#include "error.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define HOME	"HOME"
#define EXE_NAME "cd"

int		cd(int argc, char **argv, char **environ)
{
	char	*home;

	if (argc == 1)
	{
		if ((home = get_env_value(environ, HOME)) == NULL)
			return (EXIT_SUCCESS);
		if (chdir(home) == -1)
			return (error_msg_param(EXE_NAME, strerror(errno), home));
	}
	return (EXIT_SUCCESS);
}

int		main(int argc, char **argv, char **environ)
{
	return cd(argc, argv, environ);
}
