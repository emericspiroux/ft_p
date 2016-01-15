/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/27 17:59:20 by larry             #+#    #+#             */
/*   Updated: 2016/01/15 04:18:21 by larry            ###   ########.fr       */
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
		return (0);
	else
		return (head.size);
}

static int			write_header(int cs, int errorfd, char *error)
{
	t_header_ftp	head;

	init_head(&head);
	if (errorfd == -1)
	{
		head.bool_error = 1;
		ft_memcpy((char *)head.error_msg, error, ft_strlen(error));
	}
	else
		head.bool_error = 0;
	write(cs, &head, sizeof(t_header_ftp));
	return (head.bool_error);
}

static int			write_confirm(int cs, int error)
{
	t_header_ftp	head;

	init_head(&head);
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
			write_confirm(sock, 1);
			continue ;
		}
		write_confirm(sock, 0);
		r += tmp;
		write(fd, buf, tmp);
		ft_bzero(buf, 1023);
	}
	close(fd);
	ft_bzero(buf, 1023);
	return (1);
}

int					option_set(int sock, int argc, char *path)
{
	int				fd;
	int				size;

	if (argc != 2)
	{
		write_header(sock, -1, ft_strdup("ft_p : serveur : Usage : set <PathFile>\n"));
		send_confirmation(sock, 1);
		return (0);
	}
	fd = open(path, O_CREAT
						| O_WRONLY | O_RDONLY | O_TRUNC,
						S_IROTH
						| S_IRUSR
						| S_IWUSR);
	if (!write_header(sock, fd, error_open(path, 1)) && (size = read_header(sock)))
	{
		write_file(fd, sock, size);
		send_confirmation(sock, 0);
	}
	else
	{
		send_confirmation(sock, 1);
		unlink(path);
	}
	close(fd);
	return (1);
}
