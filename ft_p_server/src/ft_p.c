/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 14:49:00 by larry             #+#    #+#             */
/*   Updated: 2015/08/19 18:39:05 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

static void			usage()
{
	ft_putstr("Usage : ./server <port>\n");
	exit(-1);
}

static int			create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("bind error. (Please change acces port or waiting a while before retry)\n");
		return (-1);
	}
	listen(sock, 50);
	return (sock);
}

static void			send_ckeck(int cs)
{
	ft_putstr("Reponse Sent\n");
	write(cs, "SUCCESS\0", 8);
}

static int			do_work(int cs)
{
	int				r;
	char			buf[1024];

	ft_bzero(buf, sizeof(buf));
	while (buf[0] != '\x2')
	{
		ft_bzero(buf, 1023);
		if ((r = read(cs, buf, 1023)) <= 0)
			ft_putstr("Error Reading.\n");
		else
		{
			if (buf[0] != '\x2')
			{
				buf[r] = '\0';
				ft_putstr("Received ");
				ft_putnbr(r);
				ft_putstr(" bytes : [");
				ft_putstr(buf);
				ft_putstr("]\n");
			}
		}
		if (buf[0] != '\x2')
			send_ckeck(cs);
	}
	ft_bzero(buf, sizeof(buf));
	return (1);
}


/*

static void			send_error(int cs)
{
	ft_putstr("Reponse not Sent\n");
	write(cs, "ERROR\0", 8);
}*/

static void			do_accept(int sock)
{
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	int					ret;

	ret = 1;
	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	do_work(cs);
	close(cs);
}

int					main(int argc, char const *av[])
{
	int		port;
	int		sock;

	if (argc != 2)
		usage();
	port = ft_atoi(av[1]);
	sock = create_server(port);
	do_accept(sock);
	close(sock);
	return (0);
}
