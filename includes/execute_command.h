/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:39:00 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/29 20:39:18 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_COMMAND_H
# define EXECUTE_COMMAND_H

# include <unistd.h>

pid_t	g_child;
int		execute_command(char **argv, char ***env);
int		execute_commands(char ***argv, char ***env);
int		write_fd(int write_fd);
int		read_write_fd(int read_fd, int write_fd);
int		execute_pipe(int idx, int *fd, char ***argv, char ***env);
char	**extend_argv(char **argv, char *str);
int		check_pipe(char ***argv, char ***env, int len, int *fd);

#endif
