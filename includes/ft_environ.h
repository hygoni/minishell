/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:30:41 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/15 19:07:32 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENVIRON_H
# define FT_ENVIRON_H

int		get_equal_idx(char *str);
char	*get_env_value(char **env, char *key);
char	**cpy_env(char **environ, int len);
char	**clean_env(char **env, int size);
int		get_strarr_size(char **arr);
void	clean_arg(char *key, char *value, char **arg, char **env);
char	**realloc_env(char **env, int size);
int		check_key(char ***env, char *key, char *value);
int		add_env(char ***env, char *key, char *vaule);
void	_export(int argc, char **argv, char ***env);
void	_unset(int argc, char **argv, char ***env);
void	_env(char **env);
int		check_validate(char *str);
void	_export_one(char *key, char *value, char **env);

#endif
