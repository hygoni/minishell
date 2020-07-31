/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <jinwkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 11:41:38 by jinwkim           #+#    #+#             */
/*   Updated: 2020/08/01 00:58:02 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

char	**remove_redirection(char **argv);
int		check_redir(char *next);
int		clear_redir(int *arr, int end, char **err_file, int error);
int		clear_redir_fd(int *fd_input, int *fd_output);
int		get_redir(char **argv, int **fd_input, int **fd_output);
int		init_redir_input(int type, int **fd_arr, int *tmp, int *fd);
int		init_redir_output(int type, int *fd_out, int *tmp, int *fd);
#endif
