/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 17:55:44 by larry             #+#    #+#             */
/*   Updated: 2015/09/04 15:57:35 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int				exec_command(int cs, int argc, char **av)
{
	if (ft_strcmp(av[0], "ls") == 0)
		return (option_ls(cs, argc, av));
	if (ft_strcmp(av[0], "pwd") == 0)
		return (option_pwd(cs, argc, av));
	if (ft_strcmp(av[0], "cd") == 0)
		return (option_cd(cs, argc, av));
	if (ft_strcmp(av[0], "get") == 0)
		return (option_get(cs, argc, av));
	if (ft_strcmp(av[0], "put") == 0)
		return (option_set(cs, av[1]));
	return (0);
}

int						do_command_line(int cs, char *request)
{
	char				**argv;
	unsigned int		argc;

	if (request[0] != '\x2')
	{
		argv = ft_strsplit(request, ' ');
		argc = ft_strcontains(request, ' ');
		return (exec_command(cs, argc + 1, argv));
	}
	return (0);
}
