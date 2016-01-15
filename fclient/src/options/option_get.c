/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:49:52 by larry             #+#    #+#             */
/*   Updated: 2016/01/15 04:17:07 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int			read_header(int sock)
{
	int				r;
	t_header_ftp	head;

	r = 0;
	init_head(&head);
	while ((unsigned int)r < sizeof(t_header_ftp))
		r += read(sock, &head, sizeof(t_header_ftp));
	if (head.bool_error == 1)
	{
		ft_putstr((const char *)head.error_msg);
		return (0);
	}
	else
		return (head.size);
}

static int			write_header(int cs, int error)
{
	t_header_ftp	head;

	if (error == -1)
		head.bool_error = 1;
	else
		head.bool_error = 0;
	write(cs, &head, sizeof(t_header_ftp));
	return (head.bool_error);
}

static int			write_file(int fd, int sock, int size)
{
	char			buf[1024];
	int				r;
	int				tmp;
	int				save;

	ft_bzero(buf, 1023);
	r = 0;
	save = 0;
	tmp = 0;
	while (r < size)
	{
		save = read_header(sock);
		tmp = read(sock, buf, 1023);
		if (save != tmp)
		{
			write_header(sock, 1);
			continue ;
		}
		write_header(sock, 0);
		r += tmp;
		write(fd, buf, tmp);
		ft_bzero(buf, 1023);
	}
	close(fd);
	return (1);
}

int					option_get(int sock, char *path)
{
	int				fd;
	int				size;

	fd = open(path, O_CREAT
						| O_WRONLY | O_RDONLY | O_TRUNC,
						S_IROTH
						| S_IRUSR
						| S_IWUSR);
	if ((size = read_header(sock)) && !write_header(sock, fd))
	{
		write_file(fd, sock, size);
		read_response(sock);
	}
	else
		unlink(path);
	close(fd);
	return (1);
}
