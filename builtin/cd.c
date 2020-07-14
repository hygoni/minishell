/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:26:13 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/14 16:03:10 by hyeyoo           ###   ########.fr       */
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
#include "constant.h"

#define PWD							"PWD"
#define OLDPWD						"OLDPWD"
#define HOME						"HOME"
#define EXE_NAME					"cd"
#define TOO_MANY_ARGUMENTS			"too many arguments"
#define NO_SUCH_FILE_OR_DIRECTORY	"no such file or directory"
#define GETCWD_FAILED				"getcwd() failed"
#define ENV_ERROR					"environment variables error"

void	update_pwd(char *pwd, char **environ)
{
	char	*oldpwd;

	oldpwd = get_env_value(environ, PWD);
	if (oldpwd == NULL)
		oldpwd = pwd;
}

int		get_previous(char *buf, char **environ)
{
	char	*oldpwd;

	oldpwd = get_env_value(environ, OLDPWD);
	if (oldpwd == NULL)
		return (error_msg(EXE_NAME, ENV_ERROR));
	ft_strlcpy(buf, oldpwd, PATH_MAX);
	return (TRUE);
}

int		cd(int argc, char **argv, char **environ)
{
	char	buf[PATH_MAX];
	int		ret;
	char	*slash;
	char	*tmp;

	ft_memset(buf, 0, PATH_MAX);
	if (argc > 2)
		return (error_msg(EXE_NAME, TOO_MANY_ARGUMENTS));
	else if (getcwd(buf, PATH_MAX) == NULL)
		return (error_msg(EXE_NAME, GETCWD_FAILED));
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		if ((ret = get_previous(buf, environ)) == FALSE)
			return (ret);
	}
	else
	{
		slash = (argv[1][ft_strlen(argv[1]) - 1] == '/') ? "" : "/";
		ft_strlcat(buf, slash, PATH_MAX);
		ft_strlcat(buf, argv[1], PATH_MAX);
	}
	if (chdir(buf) == -1)
		return (error_msg_param(EXE_NAME, strerror(errno), argv[1]));
	printf("cwd : %s\n", buf);
	return (EXIT_SUCCESS);
}

int		main(int argc, char **argv, char **environ)
{
	return (cd(argc, argv, environ));
}
