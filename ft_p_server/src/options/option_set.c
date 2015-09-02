/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/27 17:59:20 by larry             #+#    #+#             */
/*   Updated: 2015/09/02 17:38:29 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int			write_file(int cs, int fd, char *path)
{
	char			buf[1024];
	int				r;
	char			*last_char;

	while ((r = read(cs, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		if (ft_strstr(buf, "ERROR\x2") != NULL)
		{
			unlink(path);
			send_confirmation(cs, 1);
			return (0);
		}
		if ((last_char = ft_strchr(buf, '\x2')) != NULL)
		{
			*last_char = '\0';
			write(fd, buf, ft_strlen(buf));
			break ;
		}
		write(fd, buf, ft_strlen(buf));
		ft_bzero(buf, 1023);
	}
	ft_bzero(buf, 1023);
	return (0);
}

int					option_set(int cs, char *path)
{
	int				fd;
	char			*error;
	char			*error_sent;

	if ((fd = open(path, O_CREAT|O_WRONLY, S_IROTH|S_IRUSR|S_IWUSR)) == -1)
	{
		error = error_open(path, 1);
		error_sent = ft_strjoin(error, ANSI_COLOR_RED"ERROR"ANSI_COLOR_RESET"\x2\0");
		write(cs, "ERROR\x2\x2", 7);
		wait_response(cs);
		write(cs, error_sent, ft_strlen(error_sent));
		return (0);
	}
	write(cs, "\x2", 1);
	write_file(cs, fd, path);
	close(fd);
	send_confirmation(cs, 0);
	return (1);
}
