/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/27 18:02:46 by larry             #+#    #+#             */
/*   Updated: 2015/09/03 19:05:53 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int			return_open(char *path, int sock)
{
	error_open(path);
	wait_response(sock);
	write(sock, "ERROR\x2", 7);
	read_response(sock);
	return (0);
}

static int			advance_wait(char *buf, int sock)
{
	int				r;

	ft_bzero(buf, 1023);
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_bzero(buf, 1023);
		if (ft_strstr(buf, "ERROR\x2\x2"))
		{
			ft_bzero(buf, 1023);
			write(sock, "\x2", 1);
			ft_bzero(buf, 1023);
			read_response(sock);
			return (0);
		}
	}
	ft_bzero(buf, 1023);
	return (1);
}

int					option_set(int sock, char *path)
{
	int				fd;
	int				r;
	char			buf[1024];

	if ((fd = open(path, O_RDWR)) == -1)
		return (return_open(path, sock));
	if (!advance_wait(buf, sock))
		return (0);
	while ((r = read(fd, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		write(sock, buf, ft_strlen(buf));
		ft_bzero(buf, 1023);
	}
	close(fd);
	write(sock, "\x2", 1);
	read_response(sock);
	return (1);
}
