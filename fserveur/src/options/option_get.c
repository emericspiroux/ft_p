/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:30:51 by larry             #+#    #+#             */
/*   Updated: 2015/09/02 17:33:39 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void		write_file(int cs, int fd)
{
	char		buf[1024];
	int			r;

	while ((r = read(fd, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		write(cs, buf, ft_strlen(buf));
		ft_bzero(buf, 1023);
	}
	write(cs, "\x2", 1);
	ft_bzero(buf, 1023);
}

int				option_get(int cs, int argc, char **argv)
{
	int			fd;
	char		*error;
	char		*error_sent;

	(void)argc;
	if ((fd = open(argv[1], O_RDWR)) == -1)
	{
		error = error_open(argv[1], 1);
		error_sent = ft_strjoin(error, ANSI_COLOR_RED"ERROR"ANSI_COLOR_RESET"\x2\0");
		write(cs, "ERROR\x2\x2", 7);
		wait_response(cs);
		write(cs, error_sent, ft_strlen(error_sent));
		return (0);
	}
	write_file(cs, fd);
	wait_response(cs);
	close(fd);
	send_confirmation(cs, 0);
	return (1);
}
