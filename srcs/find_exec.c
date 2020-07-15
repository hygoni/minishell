/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:47:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/15 20:38:33 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_environ.h"
#include "libft.h"
#include "constant.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define PATH	"PATH"
#define ENV_ERROR	"environment variables error"
#define EXE_NAME	"minishell"

char	*find_exec_sub(char *path, char *name)
{
	char		buf[PATH_MAX];
	char		*slash;
	struct stat	statbuf;

	ft_memset(buf, 0, PATH_MAX);
	ft_strlcat(buf, path, PATH_MAX);
	slash = (path[ft_strlen(path) - 1] != '/') ? "/" : "";
	slash = (ft_strlen(path) == 0) ? "" : slash;
	ft_strlcat(buf, slash, PATH_MAX);
	ft_strlcat(buf, name, PATH_MAX);
	if (stat(buf, &statbuf) == 0)
		return (ft_strdup(buf));
	else
		return (NULL);
}

char	*find_exec(char *name, char **environ)
{
	char	*path;
	char	*token;
	char	*ret;

	if ((path = get_env_value(environ, PATH)) == NULL
			|| (path = ft_strdup(path)) == NULL)
		return (NULL);
	token = ft_strtok(path, ":");
	while (token != NULL)
	{
		if ((ret = find_exec_sub(token, name)) != NULL)
		{
			free(path);
			return (ret);
		}
		token = ft_strtok(NULL, ":");
	}
	free(path);
	if ((ret = find_exec_sub("", name)) != NULL)
		return (ret);
	return (NULL);
}
