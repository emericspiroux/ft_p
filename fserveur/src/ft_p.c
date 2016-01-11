/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 14:49:00 by larry             #+#    #+#             */
/*   Updated: 2015/09/04 15:58:45 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int				create_server(int port)
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
	listen(sock, NB_ACCEPT_CLIENT);
	return (sock);
}

static int				do_work(int cs)
{
	int					r;
	char				buf[1024];
	int					ret;
	int					timeout;

	ret = 1;
	timeout = 0;
	while (ret && timeout < 10)
	{
		ft_bzero(buf, 1023);
		if ((r = read(cs, buf, 1023)) <= 0)
			timeout++;
		else
		{
			buf[r] = '\0';
			do_command_line(cs, buf);
		}
	}
	ft_bzero(buf, 1023);
	close(cs);
	return (1);
}

static int				do_accept(int sock)
{
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;

	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	return (cs);
}

static void				add_client(int sock, const char *path)
{
	pid_t				pid;
	int					cs;

	autorized_folder(1, path);
	ft_putstr(ANSI_COLOR_GREEN"[Server Started]\n"ANSI_COLOR_RESET);
	while (1)
	{
		if (!(cs = do_accept(sock)))
		{
			ft_putstr("Stack Client Full, please waiting a while.\n");
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			do_work(cs);
			break ;
		}
		else if (pid > 0)
		{
			close(cs);
			continue;
		}
	}
}

int						main(int argc, char const *av[])
{
	int					port;
	int					sock;

	if (argc > 3 || argc < 2)
	{
		ft_putstr("Usage : ./server <port> [<folder>]\n");
		exit(-1);
	}
	port = ft_atoi(av[1]);
	if ((sock = create_server(port)) == -1)
		return (0);
	add_client(sock, av[2]);
	close(sock);
	return (0);
}
