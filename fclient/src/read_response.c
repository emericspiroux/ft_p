/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_response.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 18:24:13 by larry             #+#    #+#             */
/*   Updated: 2015/09/03 18:32:56 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				read_response(int sock)
{
	char		buf[1024];
	int			r;

	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_putstr(buf);
		ft_putstr("\n");
		ft_bzero(buf, 1023);
		return (1);
	}
	return (0);
}
