/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_confirmation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 12:26:08 by larry             #+#    #+#             */
/*   Updated: 2015/08/25 18:51:31 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void			send_check(int cs)
{
	write(cs, ANSI_COLOR_GREEN"SUCCESS"ANSI_COLOR_RESET"\x2\0", 17);
}

static void			send_error(int cs)
{
	write(cs, ANSI_COLOR_RED"ERROR"ANSI_COLOR_RESET"\x2\0", 16);
}

int					send_confirmation(int cs, int message)
{
	if (message == 0)
		send_check(cs);
	else if (message != 0)
		send_error(cs);
	return (0);
}
