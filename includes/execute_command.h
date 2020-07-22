/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:39:00 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/23 08:09:53 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_COMMAND_H
# define EXECUTE_COMMAND_H
int		execute_command(char **argv, char ***env);
int		execute_commands(char **argv, char ***env);
#endif
