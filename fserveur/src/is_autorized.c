/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_autorized.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/01 16:11:19 by larry             #+#    #+#             */
/*   Updated: 2015/09/04 15:39:14 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				is_autorized(char *name, char *path, int ls_opt)
{
	int			fnode;
	int			asknode;

	fnode = autorized_folder(0, "");
	if ((asknode = ft_getInode(path)) == -1)
	{
		if (ls_opt != 1)
		{
			error_open_dir(path, 0);
			return (0);
		}
		else
			return (1);
	}

	if (asknode < fnode)
	{
		ft_putstr("ft_p: ");
		ft_putstr(name);
		ft_putstr(" : Permission denied by server.\n");
		return (0);
	}
	return (1);
}
