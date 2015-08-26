/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 19:02:27 by larry             #+#    #+#             */
/*   Updated: 2015/08/25 19:02:42 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				option_cd(int sock)
{
	int				r;
	char			buf[1024];
	int				i;

	ft_bzero(buf, 1023);
	i = 0;
	while ((r = read(sock, buf, 1023)) > 0)
	{
			i++;
			buf[r] = '\0';
			ft_putstr(buf);
			if (ft_strchr(buf, '\x2') != NULL)
				break;
			ft_bzero(buf, 1023);
	}
	ft_putstr("\n");
	return (1);
}
