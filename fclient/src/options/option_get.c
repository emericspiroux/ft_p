/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:49:52 by larry             #+#    #+#             */
/*   Updated: 2015/09/03 18:48:11 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int			write_file(int fd, int sock, char *path)
{
	char			buf[1024];
	int				r;
	char			*last_char;

	ft_bzero(buf, 1023);
	while ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		if (ft_strstr(buf, "ERROR\x2\x2") != NULL)
		{
			unlink(path);
			break ;
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
	close(fd);
	write(sock, "\x2", 1);
	return (1);
}

int					option_get(int sock, char *path)
{
	int				fd;

	if ((fd = open(path, O_CREAT
						| O_WRONLY,\
						S_IROTH
						| S_IRUSR
						| S_IWUSR)) == -1)
	{
		error_open(path);
		return (0);
	}
	write_file(fd, sock, path);
	read_response(sock);
	return (1);
}
