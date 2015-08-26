/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 14:26:33 by larry             #+#    #+#             */
/*   Updated: 2015/08/25 21:11:13 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <sys/types.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define NB_ACCEPT_CLIENT   50

/*
** Tools
*/

int		send_all(int socket, void *buffer, size_t length);
int		send_confirmation(int cs, int message);
int		ft_getInode(char *path);
int		autorized_folder(int display);

/*
** Available Commands
*/
int		option_ls(int cs, int argc, char **argv);
int		option_pwd(int cs, int argc, char **argv);
int		option_cd(int cs, int argc, char **argv);

#endif
