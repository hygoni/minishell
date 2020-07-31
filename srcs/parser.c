/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:32:05 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/30 20:04:51 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute_command.h"
#include "free.h"
#include "ft_environ.h"
#include "builtin.h"
#include "error.h"
#include "escape.h"
#include <stdlib.h>
#define EXE_NAME "minishell"
#define MSG_DOUBLE_QUOTE_NOT_CLOSED "double quote isn't closed"
#define MSG_SINGLE_QUOTE_NOT_CLOSED "single quote isn't closed"

extern int g_status;

char	*ft_strjoinc(char *str, char c)
{
	int		len;
	char	*new;

	len = ft_strlen(str) + 1;
	new = malloc(sizeof(char) * (len + 1));
	ft_strcpy(new, str);
	new[len - 1] = c;
	new[len] = '\0';
	free(str);
	return (new);
}

char	***extend_argv_3d(char ***argv, char **str)
{
	int		len;
	char	***new;
	int		i;

	len = 0;
	while (argv[len] != NULL)
		len++;
	new = malloc(sizeof(char**) * (len + 2));
	i = 0;
	while (i < len)
	{
		new[i] = argv[i];
		i++;
	}
	new[i++] = str;
	new[i] = NULL;
	free(argv);
	return (new);
}

char	**extend_argv(char **argv, char *str)
{
	int		len;
	char	**new;
	int		i;

	len = 0;
	while (argv[len] != NULL)
		len++;
	new = malloc(sizeof(char*) * (len + 2));
	i = 0;
	while (i < len)
	{
		new[i] = argv[i];
		i++;
	}
	new[i++] = str;
	new[i] = NULL;
	free(argv);
	return (new);
}

char	*parse_path_sub(int *idx, char *arg, char ***env)
{
	int		i;
	char	*token;
	char	*key;

	i = *idx;
	i++;
	key = ft_strdup("");
	while (arg[i] != '$' && arg[i] != '\0' && (ft_isalnum(arg[i])))
		key = ft_strjoinc(key, arg[i++]);
	token = get_env_value(*env, key);
	if (ft_strcmp(key, "?") == 0)
		token = ft_itoa(g_status);
	else
		token = (token == NULL) ? ft_strdup("") : ft_strdup(token);
	*idx = i;
	free(key);
	return (token);
}

char	*parse_path(char *arg, char ***env)
{
	int		i;
	char	*parsed;
	char	*token;
	char	*to_free;

	parsed = ft_strdup("");
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '$')
			token = parse_path_sub(&i, arg, env);
		else
		{
			token = ft_strdup("");
			while (arg[i] != '$' && arg[i] != '\0')
				token = ft_strjoinc(token, arg[i++]);
		}
		to_free = parsed;
		parsed = ft_strjoin(parsed, token);
		free(token);
		free(to_free);
	}
	free(arg);
	return (parsed);
}

char	*proc_single_quote(int *idx, char *arg, char *str)
{
	char	*tmp;
	int		i;
	char	*to_free;

	i = *idx;
	i++;
	if ((tmp = ft_strdup("")) == NULL)
		return (NULL);
	while (arg[i] != '\'' && arg[i] != '\0')
		if ((tmp = ft_strjoinc(tmp, arg[i++])) == NULL)
			return (NULL);
	to_free = str;
	if ((str = ft_strjoin(str, tmp)) == NULL)
		return (NULL);
	free(to_free);
	free(tmp);
	if (arg[i] == '\'')
		i++;
	else
	{
		error_msg(EXE_NAME, MSG_SINGLE_QUOTE_NOT_CLOSED);
		return (NULL);
	}
	*idx = i;
	return (str);
}

char	*proc_double_quote(int *idx, char *arg, char *str, char ***env)
{
	int		i;
	char	*tmp;
	char	*to_free;
	char	*parsed;

	i = *idx;
	i++;
	if ((tmp = ft_strdup("")) == NULL)
		return (NULL);
	while (arg[i] != '"' && arg[i] != '\0')
	{
		if (arg[i] == '\\')
		{
			i++;
			tmp = ft_strjoinc(tmp, escape(arg[i++]));
		}
		else
			tmp = ft_strjoinc(tmp, arg[i++]);
	}
	if (arg[i] == '"')
		i++;
	else
	{
		error_msg(EXE_NAME, MSG_DOUBLE_QUOTE_NOT_CLOSED);
		return (NULL);
	}
	to_free = str;
	if ((parsed = parse_path(tmp, env)) == NULL)
		return (NULL);
	if ((str = ft_strjoin(str, parsed)) == NULL)
		return (NULL);
	free(to_free);
	free(parsed);
	*idx = i;
	return (str);
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

char	*proc_semicolon(int *idx, char *str, char ***argv)
{
	int		i;

	i = *idx;
	if (ft_strlen(str) > 0)
		*argv = extend_argv(*argv, str);
	else
		free(str);
	*argv = extend_argv(*argv, ft_strdup(";"));
	str = ft_strdup("");
	i++;
	*idx = i;
	return (str);
}

char	*proc_bar(int *idx, char *str, char ***argv)
{
	int		i;

	i = *idx;
	if (ft_strlen(str) > 0)
		*argv = extend_argv(*argv, str);
	else
		free(str);
	*argv = extend_argv(*argv, ft_strdup("|"));
	str = ft_strdup("");
	i++;
	*idx = i;
	return (str);
}

char	*proc_str(int *idx, char *arg, char *str, char ***env)
{
	int		i;
	char	*tmp;
	char	*to_free;
	char	*parsed;

	i = *idx;
	tmp = ft_strdup("");
	while (arg[i] != '|' && arg[i] != ';' && arg[i] != ' '
			&& arg[i] != '\'' && arg[i] != '"' && arg[i] != '\0')
	{
		if (arg[i] == '\\')
		{
			i++;
			tmp = ft_strjoinc(tmp, arg[i++]);
		}
		else
			tmp = ft_strjoinc(tmp, arg[i++]);
	}
	to_free = str;
	parsed = parse_path(tmp, env);
	str = ft_strjoin(str, parsed);
	free(to_free);
	free(parsed);
	*idx = i;
	return (str);
}

char	**proc_quote_path(char *arg, char ***env)
{
	char	*str;
	int		i;
	char	**argv;

	if ((argv = ft_calloc(sizeof(char*), 1)) == NULL)
		return (NULL);
	if ((str = ft_strdup("")) == NULL)
		return (NULL);
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'')
			str = proc_single_quote(&i, arg, str);
		else if (arg[i] == '"')
			str = proc_double_quote(&i, arg, str, env);
		else if (arg[i] == ' ')
			str = proc_space(&i, arg, str, &argv);
		else if (arg[i] == ';')
			str = proc_semicolon(&i, str, &argv);
		else if (arg[i] == '|')
			str = proc_bar(&i, str, &argv);
		else
			str = proc_str(&i, arg, str, env);
		if (str == NULL)
			return (NULL);
		if (arg[i] == '\0')
			argv = extend_argv(argv, str);
	}
	return (argv);
}

int		find(char **argv, char *find)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (!ft_strcmp(argv[i], find))
			return (i);
		i++;
	}
	return (-1);
}

void	parse_pipes(char **argv2, char ***env)
{
	char	***argv3;
	int		i;
	int		len;
	char	**add;

	len = 0;
	while (argv2[len] != NULL)
		len++;
	argv3 = (char***)ft_calloc(sizeof(char**), 1);
	add = (char**)ft_calloc(sizeof(char*), 1);
	i = 0;
	while (i < len)
	{
		if (!ft_strcmp(argv2[i], "|"))
		{
			argv3 = extend_argv_3d(argv3, add);
			add = (char**)ft_calloc(sizeof(char*), 1);
		}
		else
			add = extend_argv(add, ft_strdup(argv2[i]));
		i++;
	}
	argv3 = extend_argv_3d(argv3, add);
	execute_commands(argv3, env);
	free_3d(argv3);
}

void	parse_commands_sub(char **argv, char ***env, int end, int len)
{
	int		start;

	start = 0;
	while (end >= 0 && start < len)
	{
		if (argv[end] != NULL)
			free(argv[end]);
		argv[end] = NULL;
		parse_pipes(&argv[start], env);
		start = end + 1;
		end = find(&argv[start], ";");
		if (end >= 0)
			end += start;
	}
	if (argv[start] != NULL && ft_strcmp(argv[start], ";") != 0)
		parse_pipes(&argv[start], env);
}

void	parse_commands(char *cmd_line, char ***env)
{
	int		end;
	int		start;
	char	**argv;
	int		len;

	len = 0;
	if (ft_strlen(cmd_line) == 0)
		return ;
	else if ((argv = proc_quote_path(cmd_line, env)) == NULL)
		return ;
	end = find(argv, ";");
	start = 0;
	while (argv[len] != NULL)
		len++;
	parse_commands_sub(argv, env, end, len);
	free_2d_len(argv, len);
}
