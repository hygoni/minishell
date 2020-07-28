/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:32:05 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/26 18:08:51 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute_command.h"
#include "free.h"
#include "ft_environ.h"
#include <stdlib.h>

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
	char		***new;
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

char	*parse_path(char *arg, char ***env)
{
	int	i;
	char	*parsed;
	char	*token;
	char	*to_free;
	char	*key;

	parsed = ft_strdup("");
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '$')
		{
			i++;
			key = ft_strdup("");
			while (arg[i] != '$' && arg[i] != '\0')
				key = ft_strjoinc(key, arg[i++]);
			token = get_env_value(*env, key);
			if (ft_strcmp(key, "?") == 0)
				token = ft_itoa(g_status);
			else
				token = (token == NULL) ? ft_strdup("") : ft_strdup(token);
		}
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

char	**ft_proc_quote_path(char *arg, char ***env)
{
	char	*str;
	int		i;
	char	**argv;
	char	*to_free;
	char	*tmp;

	argv = malloc(sizeof(char*));
	argv[0] = NULL;
	str = ft_strdup("");
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'')
		{
			i++;
			tmp = ft_strdup("");
			while (arg[i] != '\'' && arg[i] != '\0')
				tmp = ft_strjoinc(tmp, arg[i++]);
			if (arg[i] == '\'')
				i++;
			to_free = str;
			str = ft_strjoin(str, tmp);
			free(to_free);
			free(tmp);
		}
		else if (arg[i] == '"')
		{
			i++;
			tmp = ft_strdup("");
			while (arg[i] != '"' && arg[i] !='\0')
			{
				if (arg[i] == '\\')
					i++;
				tmp = ft_strjoinc(tmp, arg[i++]);
			}
			if (arg[i] == '"')
				i++;
			to_free = str;
			str = ft_strjoin(str, parse_path(tmp, env));
			free(to_free);
		}
		else if (arg[i] == ' ')
		{
			if (ft_strlen(str) > 0)
				argv = extend_argv(argv, str);
			str = ft_strdup("");
			while (arg[i] == ' ')
				i++;
		}
		else if (arg[i] == ';')
		{
			if (ft_strlen(str) > 0)	
				argv = extend_argv(argv, str);
			argv = extend_argv(argv, ft_strdup(";"));
			str = ft_strdup("");
			i++;
		}
		else if (arg[i] == '|')
		{
			if (ft_strlen(str) > 0)	
				argv = extend_argv(argv, str);
			argv = extend_argv(argv, ft_strdup("|"));
			str = ft_strdup("");
			i++;
		}
		else
		{
			tmp = ft_strdup("");
			while (arg[i] != '|' && arg[i] != ';' && arg[i] != ' ' && arg[i] != '\'' && arg[i] != '"' && arg[i] != '\0')
			{	
				if (arg[i] == '\\')
					i++;
				tmp = ft_strjoinc(tmp, arg[i++]);
			}
			to_free = str;
			str = ft_strjoin(str, parse_path(tmp, env));
			free(to_free);
		}
		if (arg[i] == '\0')
			argv = extend_argv(argv, str);
	}
	return (argv);
}

int	find(char **argv, char *find)
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
	int	i;
	int	len;
	char	**add;

	len = 0;
	while (argv2[len] != NULL)
		len++;
	argv3 = (char***)malloc(sizeof(char**));
	argv3[0] = NULL;
	add = (char**)malloc(sizeof(char*));
	add[0] = NULL;
	i = 0;
	while (i < len)
	{
		if (!ft_strcmp(argv2[i], "|"))
		{
			argv3 = extend_argv_3d(argv3, add);
			add = (char**)malloc(sizeof(char*));
			add[0] = NULL;
		}
		else
		{
			add = extend_argv(add, ft_strdup(argv2[i]));
		}
		i++;
	}
	argv3 = extend_argv_3d(argv3, add);
	execute_commands(argv3, env);
	free_3d(argv3);
}


void	parse_commands(char *cmd_line, char ***env)
{
	int	end;
	int	start;
	char	**argv;
	int	len;

	len = 0;
	argv = ft_proc_quote_path(cmd_line, env); 
	end = find(argv, ";");
	start = 0;
	while (argv[len] != NULL)
		len++;
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
