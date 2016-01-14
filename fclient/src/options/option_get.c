/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:49:52 by larry             #+#    #+#             */
/*   Updated: 2016/01/14 21:13:34 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void			display_response(char *buf)
{
	if (buf)
		ft_putstr(buf);
	ft_putchar('\n');
}

static int			write_file(int fd, int sock, char *path, int size)
{
	char			buf[1024];
	int				r;
	char			*last_char;
	char			**split;

	ft_bzero(buf, 1023);
	r = 0;
	while ((r < size))
	{
		r += read(sock, buf, 1023)) > 0
		if (ft_strstr(buf, "\x4\x2") != NULL)
		{
			display_response(buf);

			break ;
		}
		if ((last_char = ft_strchr(buf, '\x3')) != NULL)
		{
			if (*last_char != buf[0])
			{
				split = ft_strsplit(buf, '\x3');
				write(fd, split[0], ft_strlen(split[0]));
				display_response(split[1]);
			}
			else
				display_response(buf);
			break ;
		}
		write(fd, buf, ft_strlen(buf));
		ft_bzero(buf, 1023);
	}
	close(fd);
	ft_bzero(buf, 1023);
	return (1);
}

static int			read_header(int sock)
{
	int				r;
	t_header_ftp	*head;

	r = 0;
	while ((r != sizeof(t_header_ftp))
		r += read(sock, head, sizeof(t_header_ftp));
	if (head->error == 1)
	{
		ft_putstr(head->error_msg);
		return (0);
	}
	else
	{
		return (head->size);
	}


}

int					option_get(int sock, char *path)
{
	int				fd;
	int				size;

	if ((fd = open(path, O_CREAT
						| O_WRONLY | O_RDONLY | O_TRUNC,
						S_IROTH
						| S_IRUSR
						| S_IWUSR)) == -1)
	{
		error_open(path);
		return (0);
	}
	if ((size = read_header(sock)))
		write_file(fd, sock, path, size);
	else
		unlink(path);
	close(fd);
	return (1);
}
