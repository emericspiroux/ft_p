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
	if (ft_strstr(av[0], "ls") != NULL)
		return (option_ls(cs, argc, av));
	else if (ft_strstr(av[0], "pwd") != NULL)
		return (option_pwd(cs, argc, av));
	else if (ft_strstr(av[0], "cd") != NULL)
		return (option_cd(cs, argc, av));
	else if (ft_strstr(av[0], "get") != NULL)
		return (option_get(cs, argc, av));
	else if (ft_strstr(av[0], "put") != NULL)
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
