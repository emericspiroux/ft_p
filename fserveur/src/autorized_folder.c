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

static int		open_test(const char *path)
{
	DIR			*fddir;

	if ((fddir = opendir(path)) == NULL)
	{
		error_open_dir((char*)path, 0);
		return (1);
	}
	closedir(fddir);
	return (0);
}

char			*autorized_folder(int display, const char *path)
{
	static char	save_dir[PATH_MAX];
	static int	booldir = 0;

	if (ft_strlen(save_dir) <= 0)
	{
		if (ft_strlen(path) > 0)
		{
			if (open_test(path))
				ft_putstr(ANSI_COLOR_RED"Default Path Set"ANSI_COLOR_RESET);
			else
				chdir(path);
		}
		getcwd(save_dir, sizeof(save_dir));
		if (display == 1)
		{
			ft_putstr("Access limit to :");
			ft_putstr(save_dir);
			ft_putstr("\n");
		}
		booldir = 1;
	}
	return (save_dir);
}
