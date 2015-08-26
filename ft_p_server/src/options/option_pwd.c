/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 16:43:59 by larry             #+#    #+#             */
/*   Updated: 2015/08/25 18:47:20 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				option_pwd(int cs, int argc, char **argv)
{
	pid_t			pid;
	int				oldfd;
	pid_t			cpid;
	int				status;
	struct rusage	usage;

	(void)argc;
	errno = 0;
	oldfd = dup(cs);
	dup2(oldfd, 1);
	dup2(oldfd, 2);
	pid = fork();
	if (pid == 0)
		execv("/bin/pwd", argv);
	else
	{
		close(oldfd);
		cpid = wait4(pid, &status, 0, &usage);
		if (cpid == pid)
			send_confirmation(cs, WEXITSTATUS(status));
	}
	return (1);
}
