/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 16:43:59 by larry             #+#    #+#             */
/*   Updated: 2015/09/03 19:09:22 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int					option_pwd(int cs, int argc, char **argv)
{
	pid_t			pid;
	pid_t			cpid;
	int				status;
	struct rusage	usage;
	struct s_stdout	fd_save;

	fd_save = redirect_stdout(cs);
	(void)argc;
	errno = 0;
	pid = fork();
	if (pid == 0)
		execv("/bin/pwd", argv);
	else
	{
		cpid = wait4(pid, &status, 0, &usage);
		if (cpid == pid)
			send_confirmation(cs, WEXITSTATUS(status));
	}
	close_redirect_stdout(fd_save);
	return (1);
}
