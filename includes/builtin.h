/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 20:38:13 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/15 20:58:12 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_cd(int argc, char **argv, char **environ);
int		ft_echo(int argc, char **argv);
int		ft_exit(char *status);
int		ft_pwd(int argc, char **environ);

#endif
