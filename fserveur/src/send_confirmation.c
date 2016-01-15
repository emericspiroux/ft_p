/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_confirmation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 12:26:08 by larry             #+#    #+#             */
/*   Updated: 2016/01/15 01:58:16 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void			send_check(int cs)
{
	write(cs, ANSI_COLOR_GREEN"SUCCESS"ANSI_COLOR_RESET"\n\x2\0", 18);
}

static void			send_error(int cs)
{
	write(cs, ANSI_COLOR_RED"ERROR"ANSI_COLOR_RESET"\n\x2\0", 19);
}

int					send_confirmation(int cs, int message)
{
	if (message == 0)
		send_check(cs);
	else if (message != 0)
		send_error(cs);
	return (0);
}
