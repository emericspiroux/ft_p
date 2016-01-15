/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/27 18:02:46 by larry             #+#    #+#             */
/*   Updated: 2016/01/15 04:15:55 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <sys/stat.h>
#include <unistd.h>

static int			write_header(int cs, int fd, char *path)
{
	t_header_ftp	head;
	struct stat		buf;

	init_head(&head);
	if (fd == -1)
	{
		head.bool_error = 1;
		error_open(path);
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
	{
		ft_putstr((const char *)head.error_msg);
		return (0);
	}
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

int					option_set(int cs, char *path)
{
	int				fd;
	int				size;

	fd = open(path, O_RDWR);
	if (read_header(cs) && (size = write_header(cs, fd, path)))
		write_file(cs, fd, size);
	read_response(cs);
	close(fd);
	return (1);
}
