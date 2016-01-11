/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 16:01:39 by larry             #+#    #+#             */
/*   Updated: 2015/08/26 16:14:50 by larry            ###   ########.fr       */
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

char					*error_open(char *path, int ret)
{
	char				*save;
	char				*tmp;

	save = ft_strdup("ft_p : serveur : ");
	tmp = NULL;
	if (EACCES == errno)
		tmp = ft_strjoin(save, "The requested access is not allowed.\n");
	else if (EEXIST == errno)
		save = ft_strjoin(construct_path(save, path), " already exists.\n");
	else if (EINVAL == errno)
		tmp = ft_strjoin(save, "Invalid value in flags.\n");
	else if (EISDIR == errno)
		save = ft_strjoin(construct_path(save, path), " is a directory.\n");
	else if (errno == 2)
		tmp = ft_strjoin(save, "No such file or directory.\n");
	else if (errno != 0)
		tmp = ft_strjoin(save, "Unknown error.\n");
	else
		return (0);
	if (!ret)
	{
		ft_putstr(tmp);
		ft_putstr("\n");
	}
	return (tmp);
}
