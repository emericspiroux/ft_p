/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 18:24:03 by larry             #+#    #+#             */
/*   Updated: 2016/01/15 05:39:31 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int			they_autorized(int argc, char **argv)
{
	int				i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			i++;
			continue ;
		}
		if (!is_autorized("ls", argv[i], 1))
			return (0);
		i++;
	}
	return (1);
}

int					option_ls(int cs, int argc, char **argv)
{
	pid_t			pid;
	pid_t			cpid;
	int				status;
	struct rusage	usage;
	t_stdout		save_std;

	errno = 0;
	save_std = redirect_stdout(cs);
	if (argv[1] && argv[1][ft_strlen(argv[1]) - 1] == '\n')
		argv[1][ft_strlen(argv[1]) - 1] = '\0';
	if (they_autorized(argc, argv))
	{
		pid = fork();
		if (pid == 0)
			execv("/bin/ls", argv);
		else
		{
			if ((cpid = wait4(pid, &status, 0, &usage)) == pid)
				send_confirmation(cs, WEXITSTATUS(status));
		}
	}
	else
		send_confirmation(cs, 1);
	close_redirect_stdout(save_std);
	return (1);
}
