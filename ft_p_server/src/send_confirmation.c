/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_confirmation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 12:26:08 by larry             #+#    #+#             */
/*   Updated: 2015/08/21 16:12:39 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void			send_check(int cs)
{
	write(cs, "SUCCESS\x2\0", 8);
}

static void			send_error(int cs)
{
	write(cs, "ERROR\x2\0", 6);
}

int					send_confirmation(int cs, int message)
{
	if (message == 1)
		send_check(cs);
	else if (message == -1)
		send_error(cs);
	return (0);
}
