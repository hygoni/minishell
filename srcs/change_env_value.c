/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:31:21 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/13 21:52:09 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_environ.h"

int		change_env_value(char *key, char *value, char **env)
{
	char	*result;
	char	*sub;

	if ((sub = ft_strjoin(key, "=")) == 0)
		return (0);
	if ((result = ft_strjoin(sub, value)) == 0)
	{
		free(sub);
		return (0);
	}
	free(sub);
	free(*env);
	*env = result;
	return (1);
}

int		check_key(char ***env, char *key, char *value)
{
	int		equal;
	char	**env_ptr;

	env_ptr = *env;
	while (*env_ptr != 0)
	{
		equal = get_equal_idx(*env_ptr);
		if (ft_strncmp(*env_ptr, key, equal) == 0)
			return (change_env_value(key, value, env_ptr));
		env_ptr++;
	}
	return (add_env(env, key, value));
}
