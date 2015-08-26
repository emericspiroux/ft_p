/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getINode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 18:00:17 by larry             #+#    #+#             */
/*   Updated: 2015/08/21 18:09:49 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		ft_getInode(char *path)
{
	DIR				*rep;
	struct dirent	*rf;

	rf = NULL;
	rep = NULL;
	if ((rep = opendir(path)) == NULL)
		return (-1);
	rf = readdir(rep);
	if (closedir(rep) == -1)
		return (-1);
	return (rf->d_ino);
}
