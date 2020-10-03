/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_token1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:14:58 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/10/04 02:52:46 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include "error.h"
#include "free.h"

char	**proc_quote_path_sub(char **argv, char *arg, char ***env, char **str)
{
	int		i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'')
			*str = proc_single_quote(&i, arg, *str);
		else if (arg[i] == '"')
			*str = proc_double_quote(&i, arg, *str, env);
		else if (arg[i] == ' ')
			*str = proc_space(&i, arg, *str, &argv);
		else if (arg[i] == ';')
			*str = proc_semicolon(&i, *str, &argv, len_2d(argv));
		else if (arg[i] == '|')
			*str = proc_bar(&i, *str, &argv, len_2d(argv));
		else if (arg[i] == '*')
			*str = proc_wildcard(&i, *str, &argv);
		else
			*str = proc_str(&i, arg, *str, env);
		if (*str == NULL && free_2d(argv))
			return (NULL);
	}
	return (argv);
}

char	**proc_quote_path(char *arg, char ***env)
{
	char	*str;
	char	**argv;
	int		len;

	if ((argv = ft_calloc(sizeof(char*), 1)) == NULL)
		return (NULL);
	if ((str = ft_strdup("")) == NULL)
		return (NULL);
	argv = proc_quote_path_sub(argv, arg, env, &str);
	if (str == NULL || argv == NULL)
		return (NULL);
	if (ft_strlen(str) > 0)
		argv = extend_argv(argv, str);
	else
		free(str);
	len = 0;
	while (argv[len] != NULL)
		len++;
	if (len != 0 && *(argv[len - 1]) == '|')
	{
		free_2d(argv);
		error_msg_parse("|");
		return (NULL);
	}
	return (argv);
}

char	*proc_space(int *idx, char *arg, char *str, char ***argv)
{
	int		i;

	i = *idx;
	if (ft_strlen(str) > 0)
		*argv = extend_argv(*argv, str);
	else
		free(str);
	str = ft_strdup("");
	while (arg[i] == ' ')
		i++;
	*idx = i;
	return (str);
}

char	*proc_semicolon(int *idx, char *str, char ***argv, int len)
{
	int			i;
	char		*semicolon;

	i = *idx;
	if ((semicolon = ft_strdup(";")) == NULL)
		return (NULL);
	if (ft_strlen(str) > 0)
		*argv = extend_argv(*argv, str);
	else
		free(str);
    len = len_2d(*argv);
	if ((*argv)[0] == NULL || ft_strlen((*argv)[0]) == 0 ||
			*((*argv)[len - 1]) == ';')
	{
		free(semicolon);
		error_msg_parse(semicolon);
		return (NULL);
	}
	if ((str = ft_strdup("")) == NULL)
		return (NULL);
	if ((*argv = extend_argv(*argv, semicolon)) == NULL)
		return (NULL);
	i++;
	*idx = i;
	return (str);
}

char	*proc_bar(int *idx, char *str, char ***argv, int len)
{
	int			i;
	char		*bar;

	i = *idx;
	if (ft_strlen(str) > 0)
		*argv = extend_argv(*argv, str);
	else
		free(str);
    len = len_2d(*argv);
	if ((*argv)[0] == NULL || ft_strlen((*argv)[0]) == 0 ||
			*((*argv)[len - 1]) == '|')
	{
		error_msg_parse("|");
		return (NULL);
	}
	if ((bar = ft_strdup("|")) == NULL)
		return (NULL);
	if ((*argv = extend_argv(*argv, bar)) == NULL)
		return (NULL);
	if ((str = ft_strdup("")) == NULL)
		return (NULL);
	i++;
	*idx = i;
	return (str);
}
