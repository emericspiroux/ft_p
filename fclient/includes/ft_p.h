/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 14:26:33 by larry             #+#    #+#             */
/*   Updated: 2015/09/04 14:24:29 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netdb.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <sys/time.h>
# include <netinet/in.h>
# include <arpa/inet.h>

int			error_open(char *path);
int			send_all(int sock, void *buffer, size_t length);
int			read_response(int sock);
int			wait_response(int sock);
int			is_command(char *argv);

int			option_ls(int sock);
int			option_pwd(int sock);
int			option_cd(int sock);
int			option_get(int sock, char *path);
int			option_set(int sock, char *path);

#endif