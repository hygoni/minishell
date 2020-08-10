/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:30:41 by jinwkim           #+#    #+#             */
/*   Updated: 2020/08/10 16:55:01 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENVIRON_H
# define FT_ENVIRON_H

int		get_equal_idx(char *str);
char	*get_env_value(char **env, char *key);
char	**cpy_env(char **environ, int len);
char	**clean_env(char **env, int size);
int		get_strarr_size(char **arr);
int		get_strarr_size3(char ***arr);
void	clean_arg(char **key, char **value, char ***arg, char ***env);
char	**realloc_env(char **env, int size);
int		check_key(char ***env, char *key, char *value);
int		ft_export(int argc, char **argv, char ***env);
int		ft_unset(int argc, char **argv, char ***env);
int		ft_env(char **env);
int		check_validate(char *str);
void	ft_export_one(char *key, char *value, char **env);
int		export_no_arg(char *name, char **env);
int		set_key(char *str, char **key);
int		set_value(char *str, char **value);

#endif
