/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:49:52 by larry             #+#    #+#             */
/*   Updated: 2015/08/27 17:27:04 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				option_get(int sock, char *path)
{
	int				r;
	char			buf[1024];
	int				i;
	int				brk;
	int				fd;
	char			*last_char;

	ft_bzero(buf, 1023);
	i = 0;
	brk = 0;
	if ((fd = open(path, O_CREAT|O_WRONLY, S_IROTH|S_IRUSR|S_IWUSR)) == -1)
		return (error_open(path));
	while ((r = read(sock, buf, 1023)) > 0)
	{
			buf[r] = '\0';
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
	ft_bzero(buf, 1023);
	write(sock, "\x2", 1);
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_putstr(buf);
		ft_putstr("\n");
		ft_bzero(buf, 1023);
	}
	else
		ft_putstr("ft_p : get : no response from serveur\n");
	return (1);
}
