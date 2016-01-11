/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 16:01:39 by larry             #+#    #+#             */
/*   Updated: 2015/08/28 04:18:24 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			error_open(char *path)
{
	ft_putstr("ft_p : client : ");
	if (EACCES == errno)
		ft_putstr("The requested access to the file is not allowed\n");
	else if (EDQUOT == errno)
		ft_putstr("Disk blocks or inodes has been exhausted\n");
	else if (EEXIST == errno)
		ft_putstr("Already exists\n");
	else if (EINVAL == errno)
		ft_putstr("Invalid value in flags.\n");
	else if (EISDIR == errno)
	{
		ft_putstr(path);
		ft_putstr(" is a directory.\n");
	}
	else if (errno == 2)
		ft_putstr("No such file or directory.\n");
	else if (errno != 0)
	{
		ft_putstr("Errno number : ");
		ft_putnbr(errno);
		ft_putstr("\n");
	}
	errno = 0;
}
