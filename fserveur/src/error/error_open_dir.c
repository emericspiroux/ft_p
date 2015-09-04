/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_open_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/01 16:19:29 by larry             #+#    #+#             */
/*   Updated: 2015/09/01 17:25:28 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char			*error_open_dir(char *path, int ret)
{
	char		*save;
	char		*tmp;

	save = ft_strdup("ft_p : serveur : ");
	if (EACCES == errno)
		tmp = ft_strjoin(save, "Permission denied.\n");
	else if (EBADF == errno)
		tmp = ft_strjoin(save, "file descriptor is not a valid for reading.\n");
	else if (ENOTDIR == errno)
	{
		tmp = ft_strjoin(save, path);
		free(save);
		save = ft_strjoin(tmp, " is not a directory.\n");
		free(tmp);
		tmp = ft_strdup(save);
	}
	else if (EMFILE == errno)
		tmp = ft_strjoin(save, "Too many file descriptors in use by process.\n");
	else if (ENFILE == errno)
		tmp = ft_strjoin(save, "Too many files are currently open in the system.\n");
	else if (ENOENT == errno)
		tmp = ft_strjoin(save, "Directory does not exist, or is empty string\n");
	else if (errno == 2)
		tmp = ft_strjoin(save, "No such file or directory.\n");
	else if (errno != 0)
		tmp = ft_strjoin(save, "Unknown error.\n");
	else
		return (0);
	if (!ret)
	{
		ft_putstr(tmp);
	}
	errno = 0;
	return (tmp);
}
