/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:32:05 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/22 11:51:36 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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

char	*parse_path(char *arg)
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
		{
			i++;
			token = ft_strdup("");
			while (arg[i] != '$' && arg[i] != '\0')
				token = ft_strjoinc(token, arg[i++]);
			printf("key : %s\n", token);	
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

char	**ft_proc_quote_path(char *arg)
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
				tmp = ft_strjoinc(tmp, arg[i++]);
			if (arg[i] == '"')
				i++;
			to_free = str;
			str = ft_strjoin(str, parse_path(tmp));
			free(to_free);
		}
		else if (arg[i] == ' ')
		{
			argv = extend_argv(argv, str);
			str = ft_strdup("");
			while (arg[i] == ' ')
				i++;
		}
		else
		{
			tmp = ft_strdup("");
			while (arg[i] != ' ' && arg[i] != '\'' && arg[i] != '"' && arg[i] != '\0')
				tmp = ft_strjoinc(tmp, arg[i++]);
			to_free = str;
			str = ft_strjoin(str, parse_path(tmp));
			free(to_free);
		}
		if (arg[i] == '\0')
			argv = extend_argv(argv, str);
	}
	return (argv);
}

int		main(int argc, char **argv)
{
	char	**ret;

	ret = ft_proc_quote_path(argv[1]);
	int i = 0;
	while (ret[i] != NULL)
	{
		printf("%s\n", ret[i]);
		i++;
	}
}
