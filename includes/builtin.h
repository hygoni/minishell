/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 20:38:13 by jinwkim           #+#    #+#             */
/*   Updated: 2020/08/10 20:16:26 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_cd(int argc, char **argv, char **environ);
int		ft_echo(int argc, char **argv);
int		ft_exit(char **argv, int size);
int		ft_pwd(int argc, char **environ);

#endif
