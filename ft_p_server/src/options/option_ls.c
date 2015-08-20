/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 18:24:03 by larry             #+#    #+#             */
/*   Updated: 2015/08/20 19:29:31 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				option_ls(int argc, char **argv)
{
	(void)argc;
	if (execv("/bin/ls", argv) == -1)
	{
		ft_putnbr(errno);
		ft_putstr("\n");
		return (-1);
	}
	else
	{
		return (1);
	}
}
