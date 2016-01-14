/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:49:52 by larry             #+#    #+#             */
/*   Updated: 2016/01/14 16:33:28 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void			display_response(char *buf)
{
	if (buf)
		ft_putstr(buf);
	ft_putchar('\n');
}

static int			write_file(int fd, int sock, char *path)
{
	char			buf[1024];
	int				r;
	char			*last_char;
	char			**split;

	ft_bzero(buf, 1023);
	while ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		if (ft_strstr(buf, "\x4\x2") != NULL)
		{
			display_response(buf);
			unlink(path);
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

int					option_get(int sock, char *path)
{
	int				fd;

	if ((fd = open(path, O_CREAT
						| O_WRONLY | O_RDONLY | O_TRUNC,
						S_IROTH
						| S_IRUSR
						| S_IWUSR)) == -1)
	{
		error_open(path);
		return (0);
	}
	write_file(fd, sock, path);
	return (1);
}
