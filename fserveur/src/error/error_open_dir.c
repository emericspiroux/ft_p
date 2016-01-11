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

static const char		*construct_path(char *save, char *path)
{
	const char			*tmp;

	tmp = ft_strjoin(save, path);
	free(save);
	return (tmp);
}

char					*error_open_dir(char *path, int ret)
{
	char				*save;
	char				*tmp;

	save = ft_strdup("ft_p : serveur : ");
	tmp = NULL;
	if (EACCES == errno)
		tmp = ft_strjoin(save, "Permission denied.\n");
	else if (EBADF == errno)
		tmp = ft_strjoin(save, "file descriptor is not a valid.\n");
	else if (ENOTDIR == errno)
		save = ft_strjoin(construct_path(save, path), " is not a directory.\n");
	else if (EMFILE == errno)
		tmp = ft_strjoin(save, "Too many file descriptors in use.\n");
	else if (ENOENT == errno)
		tmp = ft_strjoin(save, "Directory does not exist.\n");
	else if (errno == 2)
		tmp = ft_strjoin(save, "No such file or directory.\n");
	else if (errno != 0)
		tmp = ft_strjoin(save, "Unknown error.\n");
	else
		return (0);
	if (!ret)
		ft_putstr(tmp);
	errno = 0;
	return (tmp);
}
