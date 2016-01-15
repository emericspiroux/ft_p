/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 04:16:18 by larry             #+#    #+#             */
/*   Updated: 2016/01/15 04:16:30 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			init_head(t_header_ftp *head)
{
	head->bool_error = 0;
	ft_bzero(head->error_msg, BUFF_ERROR_MSG);
	head->size = 0;
}
