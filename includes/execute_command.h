/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:39:00 by jinwkim           #+#    #+#             */
/*   Updated: 2020/07/28 11:38:15 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_COMMAND_H
# define EXECUTE_COMMAND_H

int		execute_command(char **argv, char ***env);
int		execute_commands(char ***argv, char ***env);
char	**remove_redirection(char **argv);
int		write_fd(int write_fd);
int		read_write_fd(int read_fd, int write_fd);
int		execute_pipe(int idx, int *fd, char ***argv, char ***env);
int		init_redir_input(int len, int *fd_input, int *tmp, int *fd);
int		init_redir_output(int type, int *fd_out, int *origin);
char	**extend_argv(char **argv, char *str);
int		check_pipe(char ***argv, char ***env, int len, int *fd);

#endif
