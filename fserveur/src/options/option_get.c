/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:30:51 by larry             #+#    #+#             */
/*   Updated: 2016/01/15 04:18:25 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <sys/stat.h>
#include <unistd.h>

static int			write_header(int cs, int fd, char *error)
{
	t_header_ftp	head;
	struct stat		buf;
	char			*error_sent;

	init_head(&head);
	if (error != NULL)
	{
		head.bool_error = 1;
		error_sent = ft_strjoin(error, ANSI_COLOR_RED"ERROR"ANSI_COLOR_RESET"\n\0");
		ft_memcpy((char *)head.error_msg, error_sent, ft_strlen(error_sent));
	}
	else if (!fstat(fd, &buf))
		head.size = buf.st_size;
	write(cs, &head, sizeof(t_header_ftp));
	return (head.size);
}

static int			write_size(int cs, int size)
{
	t_header_ftp	head;

	init_head(&head);
	head.size = size;
	write(cs, &head, sizeof(t_header_ftp));
	return (head.size);
}

static int			read_header(int sock)
{
	int				r;
	t_header_ftp	head;

	r = 0;
	while (r != sizeof(t_header_ftp))
		r += read(sock, &head, sizeof(t_header_ftp));
	if (head.bool_error == 1)
		return (0);
	else
		return (1);
}

static void			write_file(int cs, int fd, int size)
{
	char			buf[1024];
	int				r;
	int				tmp;
	int				save;

	r = 0;
	save = 0;
	while (r < size)
	{
		ft_bzero(buf, 1023);
		tmp = read(fd, buf, 1023);
		write_size(cs, tmp);
		write(cs, buf, tmp);
		if (!read_header(cs))
		{
			lseek(fd, save, SEEK_SET);
			continue ;
		}
		r += tmp;
		save = tmp;
	}
}

int					option_get(int cs, int argc, char **argv)
{
	int				fd;
	int				size;
	char			*error;

	error = ft_strdup("ft_p : serveur : Usage : get <PathFile>\n");
	if (argc != 2)
	{
		write_header(cs, -1, error);
		return (0);
	}
	if ((fd = open(argv[1], O_RDWR)) == -1)
	{
		write_header(cs, fd, error_open(argv[1], 1));
		return (0);
	}
	if ((size = write_header(cs, fd, NULL)) && read_header(cs))
	{
		write_file(cs, fd, size);
		send_confirmation(cs, 0);
	}
	close(fd);
	return (1);
}
