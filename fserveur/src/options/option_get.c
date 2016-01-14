/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:30:51 by larry             #+#    #+#             */
/*   Updated: 2016/01/14 20:41:41 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include "get_next_line.h"
#include <sys/stat.h>

static void			write_file(int cs, int fd)
{
	char			buf[1024];
	int				r;

	while ((r = read(fd, buf, 1023)) > 0)
	{
		write(cs, buf, r);
		ft_bzero(buf, 1023);
	}
	write(cs, "\x3", 1);
	ft_bzero(buf, 1023);
	send_confirmation(cs, 0);
}

static void			write_header(int cs, int fd, char *error)
{
	t_header_ftp	head;
	struct stat		buf;
	char			*error_sent;

	if (error != NULL)
	{
		head.bool_error = 1;
		error_sent = ft_strjoin(error, ANSI_COLOR_RED"ERROR"ANSI_COLOR_RESET"\x2\0");
		ft_memcpy(&head.error_msg, &error, BUFF_ERROR_MSG);
	}
	if (fstat(fd, &buf))
		head.size = buf.st_size;
	write(cs, &head, sizeof(t_header_ftp));
}

int					option_get(int cs, int argc, char **argv)
{
	int				fd;
	char			*error;

	if (argc != 2)
	{
		error = ft_strdup("ft_p : serveur : Usage : get <PathFile>\n");
		write_header(cs, fd, error_sent)
		return (0);
	}
	if (argv[1][ft_strlen(argv[1]) - 1] == '\n')
		argv[1][ft_strlen(argv[1]) - 1] = '\0';
	if ((fd = open(argv[1], O_RDWR)) == -1)
	{
		error = error_open(argv[1], 1);
		write_header(cs, fd, error)
		return (0);
	}
	write_header(cs, fd, NULL);
	write_file(cs, fd);
	close(fd);
	return (1);
}
