/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:30:51 by larry             #+#    #+#             */
/*   Updated: 2015/08/27 17:28:23 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				option_get(int cs, int argc, char **argv)
{
	int			fd;
	int			r;
	char		buf[1024];

	(void)argc;
	if ((fd = open(argv[1], O_RDWR)) == -1)
	{
		write(cs, "\x2", 1);
		error_open(argv[1]);
		send_confirmation(cs, 0);
		return (0);
	}
	ft_bzero(buf, 1023);
	while ((r = read(fd, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		write(cs, buf, ft_strlen(buf));
		ft_bzero(buf, 1023);
	}
	write(cs, "\x2", 1);
	ft_bzero(buf, 1023);
	if ((r = read(cs, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_bzero(buf, 1023);
	}
	close(fd);
	send_confirmation(cs, 0);
	return (1);
}
