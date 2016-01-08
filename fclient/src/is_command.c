/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/04 14:23:22 by larry             #+#    #+#             */
/*   Updated: 2015/09/04 14:24:04 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				is_command(char *argv)
{
	if (ft_strcmp(argv, "ls") == 0
		|| ft_strcmp(argv, "pwd") == 0
		|| ft_strcmp(argv, "quit") == 0
		|| ft_strcmp(argv, "cd") == 0
		|| ft_strcmp(argv, "get") == 0
		|| ft_strcmp(argv, "put") == 0)
		return (1);
	return (0);
}
