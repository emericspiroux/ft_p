/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 18:24:03 by larry             #+#    #+#             */
/*   Updated: 2015/08/26 15:31:18 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				option_ls(int cs, int argc, char **argv)
{
	pid_t			pid;
	int				oldfd;
	int				save_stdout;
	int				save_stderror;
	pid_t			cpid;
	int				status;
	struct rusage	usage;

	(void)argc;
	errno = 0;
	oldfd = dup(cs);
	save_stdout = dup(1);
	save_stderror = dup(2);
	dup2(oldfd, 1);
	dup2(oldfd, 2);
	pid = fork();
	if (pid == 0)
	{
		execv("/bin/ls", argv);
		close(oldfd);
	}
	else
	{
		cpid = wait4(pid, &status, 0, &usage);
		if (cpid == pid)
			send_confirmation(cs, WEXITSTATUS(status));
		close(oldfd);
	}
	dup2(save_stdout, 1);
	dup2(save_stderror, 2);
	close(save_stdout);
	close(save_stderror);
	close(oldfd);
	return (1);
}
