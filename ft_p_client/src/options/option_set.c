/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/27 18:02:46 by larry             #+#    #+#             */
/*   Updated: 2015/09/01 15:55:14 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				option_set(int sock, char *path)
{
	int			fd;
	int			r;
	char		buf[1024];

	ft_putstr("1 Open\n");
	if ((fd = open(path, O_RDWR)) == -1)
	{
		ft_putstr("1 Error\n");
		error_open(path);
		ft_putstr("1 Read\n");
		if ((r = read(sock, buf, 1023)) > 0)
		{
			buf[r] = '\0';
			ft_bzero(buf, 1023);
		}
		ft_putstr("1 Write Error\n");
		write(sock, "ERROR\x2", 7);
		ft_putstr("1 Read Error server\n");
		if ((r = read(sock, buf, 1023)) > 0)
		{
			buf[r] = '\0';
			ft_putstr(buf);
			ft_putstr("\n");
			ft_bzero(buf, 1023);
		}
		return (0);
	}
	ft_putstr("2\n");
	ft_bzero(buf, 1023);
	ft_putstr("3 Read\n");
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_bzero(buf, 1023);
		if (ft_strstr(buf, "ERROR\x2\x2"))
		{
			ft_putstr("4 Read ERROR\n");
			ft_bzero(buf, 1023);
			write(sock, "\x2", 1);
			ft_bzero(buf, 1023);
			if ((r = read(sock, buf, 1023)) > 0)
			{
				buf[r] = '\0';
				ft_putstr(buf);
				ft_putstr("\n");
				ft_bzero(buf, 1023);
			}
			return (0);
		}
	}
	ft_putstr("5 Read\n");
	while ((r = read(fd, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		write(sock, buf, ft_strlen(buf));
		ft_bzero(buf, 1023);
	}
	close(fd);
	ft_putstr("6 write\n");
	write(sock, "\x2", 1);
	ft_bzero(buf, 1023);
	ft_putstr("7 read\n");
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_putstr(buf);
		ft_putstr("\n");
		ft_bzero(buf, 1023);
	}
	ft_putstr("8 End\n");
	ft_bzero(buf, 1023);
	return (1);
}
