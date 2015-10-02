/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autorized_folder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 20:49:34 by larry             #+#    #+#             */
/*   Updated: 2015/09/04 15:40:42 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int					autorized_folder(int display, const char *path)
{
	char			save_dir[PATH_MAX];
	static int		fnode = 0;

	if (fnode == 0)
	{
		if (ft_strlen(path) > 0)
			chdir(path);
		getcwd(save_dir, sizeof(save_dir));
		if (display == 1)
		{
			ft_putstr("Access limit to :");
			ft_putstr(save_dir);
			ft_putstr("\n");
		}
		if ((fnode = ft_getInode(save_dir)) == -1)
		{
			ft_putstr("Error on read base Folder.\n");
			exit(1);
		}
		ft_bzero(save_dir, PATH_MAX);
	}
	return (fnode);
}