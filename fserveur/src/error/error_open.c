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

char			*error_open(char *path, int ret)
{
	char		*save;
	char		*tmp;

	save = ft_strdup("ft_p : serveur : ");
	if (EACCES == errno)
		tmp = ft_strjoin(save, "The requested access to the file is not allowed.\n");
	else if (EDQUOT == errno)
		tmp = ft_strjoin(save, "disk blocks or inodes has been exhausted.\n");
	else if (EEXIST == errno)
	{
		tmp = ft_strjoin(save, path);
		free(save);
		save = ft_strjoin(tmp, " already exists.\n");
		free(tmp);
		tmp = ft_strdup(save);
	}
	else if (EINVAL == errno)
		tmp = ft_strjoin(save, "Invalid value in flags.\n");
	else if (EISDIR == errno)
	{
		tmp = ft_strjoin(save, path);
		free(save);
		save = ft_strjoin(tmp, " is a directory.\n");
		free(tmp);
		tmp = ft_strdup(save);
	}
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
