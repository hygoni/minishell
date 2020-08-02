/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:37:22 by jinwkim           #+#    #+#             */
/*   Updated: 2020/08/02 16:32:09 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

void	parse_commands(char *cmd_line, char ***env);
char	*ft_strjoinc(char *str, char c);
char	**extend_argv(char **argv, char *str);
char	***extend_argv_3d(char ***argv, char **str);
char	*parse_path(char *arg, char ***env);
int		find(char **argv, char *find);
char	**proc_quote_path(char *arg, char ***env);

char	*proc_bar(int *idx, char *str, char ***argv);
char	*proc_semicolon(int *idx, char *str, char ***argv);
char	*proc_space(int *idx, char *arg, char *str, char ***argv);
char	*proc_str(int *idx, char *arg, char *str, char ***env);

char	*proc_single_quote(int *idx, char *arg, char *str);
char	*proc_double_quote(int *idx, char *arg, char *str, char ***env);

#endif
