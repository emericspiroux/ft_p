/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 16:34:29 by larry             #+#    #+#             */
/*   Updated: 2015/09/03 19:09:23 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

struct s_stdout		redirect_stdout(int cs)
{
	t_stdout		fd;

	fd.oldfd = dup(cs);
	fd.save_stdout = dup(1);
	fd.save_stderror = dup(2);
	dup2(fd.oldfd, 1);
	dup2(fd.oldfd, 2);
	return (fd);
}
