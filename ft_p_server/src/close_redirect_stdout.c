/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_redirect_stdout.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 16:54:58 by larry             #+#    #+#             */
/*   Updated: 2015/09/02 17:06:51 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				close_redirect_stdout(struct s_stdout fd)
{
		dup2(fd.save_stdout, 1);
		dup2(fd.save_stderror, 2);
		if (close(fd.save_stdout) == -1
		|| close(fd.save_stderror) == -1
		|| close(fd.oldfd) == -1)
			return (-1);
		else
			return (0);
}
