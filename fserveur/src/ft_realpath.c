/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 16:54:58 by larry             #+#    #+#             */
/*   Updated: 2015/09/02 17:06:51 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char		*ft_realpath(const char *askpath)
{
	char	save_dir[PATH_MAX];
	char	save_askdir[PATH_MAX];
	char	*ret;

	getcwd(save_dir, sizeof(save_dir));
	if (chdir(askpath) != 0)
		return (NULL);
	getcwd(save_askdir, sizeof(save_askdir));
	chdir(save_dir);
	ret = ft_strdup(save_askdir);
	return (ret);
}
