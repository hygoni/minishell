/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:26:13 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/15 20:54:04 by jinwkim          ###   ########.fr       */
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
#include <sys/stat.h>
#include "constant.h"

#define PWD							"PWD"
#define OLDPWD						"OLDPWD"
#define HOME						"HOME"
#define EXE_NAME					"cd"
#define TOO_MANY_ARGUMENTS			"too many arguments"
#define NO_SUCH_FILE_OR_DIRECTORY	"no such file or directory"
#define GETCWD_FAILED				"getcwd() failed"
#define ENV_ERROR					"environment variables error"

int		update_pwd(char *pwd, char **environ)
{
	char	*oldpwd;

	oldpwd = get_env_value(environ, PWD);
	if (oldpwd == NULL)
		return (error_msg(EXE_NAME, ENV_ERROR));
	ft_export_one(OLDPWD, oldpwd, environ);
	ft_export_one(PWD, pwd, environ);
	return (-1);
}

int		get_from_env(char *buf, char *key, char **environ)
{
	char	*value;

	value = get_env_value(environ, key);
	if (value == NULL)
		return (error_msg(EXE_NAME, ENV_ERROR));
	ft_strlcpy(buf, value, PATH_MAX);
	return (-1);
}

void	cd_sub(char *buf, char *path)
{
	struct stat		statbuf;
	char			*slash;

	if (lstat(path, &statbuf) == 0) {
		ft_strlcpy(buf, path, PATH_MAX);
	}
	else
	{
		slash = (path[ft_strlen(path) - 1] == '/') ? "" : "/";
		ft_strlcat(buf, slash, PATH_MAX);
		ft_strlcat(buf, path, PATH_MAX);
	}
}

int		cd(int argc, char **argv, char **environ)
{
	char	buf[PATH_MAX];
	int		ret;

	ft_memset(buf, 0, PATH_MAX);
	if (argc != 2)
		return ((argc == 1) ? 0 : error_msg(EXE_NAME, TOO_MANY_ARGUMENTS));
	else if (getcwd(buf, PATH_MAX) == NULL)
		return (error_msg(EXE_NAME, GETCWD_FAILED));
	else if (ft_strcmp(argv[1], "-") == 0 || ft_strcmp(argv[1], "~") == 0)
	{
		if ((ret = get_from_env(buf, *(argv[1]) == '-' ?
						OLDPWD : HOME, environ)) >= 0)
			return (ret);
	}
	else
		cd_sub(buf, argv[1]);
	if (chdir(buf) == -1 || getcwd(buf, PATH_MAX) == NULL)
		return (error_msg_param(EXE_NAME, strerror(errno), argv[1]));
	if ((ret = update_pwd(buf, environ)) >= 0)
		return (ret);
	return (EXIT_SUCCESS);
}
