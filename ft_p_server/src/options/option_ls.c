/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 18:24:03 by larry             #+#    #+#             */
/*   Updated: 2015/08/21 16:19:41 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				option_ls(int cs, int argc, char **argv)
{
	pid_t			pid;
	int				oldfd;
	(void)argc;

	oldfd = dup(cs);
	dup2(oldfd, 1);
	dup2(oldfd, 2);
	pid = fork();
	if (pid == 0)
	{
		if (execv("/bin/ls", argv) == -1)
		{
			send_confirmation(oldfd, -1);
		}
		send_confirmation(oldfd, 1);
		return (0);
	}
	else
	{
		close(oldfd);
		wait(NULL);
	}
	return (1);
}
