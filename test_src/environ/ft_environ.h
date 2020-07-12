/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:30:41 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/12 18:00:45 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_ENVIRON_H
# define FT_ENVIRON_H

int		get_equal_idx(char *str);
char	*get_env_value(char **env, char *key);
char	**cpy_env(char **environ, int len);
char	**clean_env(char **env, int size);
int		get_strarr_size(char **arr);
void	clean_arg(char *key, char *value, char **arg, char **env);
char	**realloc_env(char **env, int size);
void	builtin_export(int argc, char **argv, char ***env);

#endif
