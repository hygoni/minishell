/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 20:38:13 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/14 21:52:30 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		cd(int argc, char **argv, char **environ);
void	echo(int argc, char **argv);
void	_exit(int status);
int		pwd(int argc, char **argv, char **environ);

#endif
