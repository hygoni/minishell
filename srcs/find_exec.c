/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:47:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/15 19:02:17 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_environ.h"
#include "libft.h"
#define PATH	"PATH"
#define ENV_ERROR	"environment variables error"
#define EXE_NAME	"minishell"

int		find_exec_sub(char *pathname, char *name)
{
	char		buf[PATH_MAX];
	char		*slash;
	struct stat	statbuf;

	ft_memeset(buf, 0, PATH_MAX);
	ft_strlcat(buf, pathname, PATH_MAX);
	slash = (pathname[ft_strlen(pathname) - 1] == '/') ? "/" : "";
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

	if ((path = ft_strdup(get_env_value(name, environ))) == NULL)
		return (NULL);
	token = ft_strtok(path, ":");
	while (token != NULL)
	{
		if ((ret = find_exec_sub(token, name)) != NULL)
			return (ret);
		token = ft_strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
