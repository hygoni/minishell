/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:48:19 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/25 16:11:07 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int		error_msg(char *name, char *msg);
int		error_msg_param(char *name, char *msg, char *param);
int		error_msg_parse(char *param);

#endif
