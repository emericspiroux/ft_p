/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 14:49:00 by larry             #+#    #+#             */
/*   Updated: 2015/08/21 16:20:03 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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
	listen(sock, NB_ACCEPT_CLIENT);
	return (sock);
}

static int			exec_command(int cs, int argc, char **argv)
{
	if (ft_strcmp(argv[0], "ls") == 0)
			return (option_ls(cs, argc, argv));
	return (0);
}

static int			do_command_line(int cs, char *request)
{
	char			**argv;
	unsigned int	argc;

	if (request[0] != '\x2')
	{
		argv = ft_strsplit(request, ' ');
		argc = ft_strcontains(request, ' ');
		return (exec_command(cs, argc, argv));
	}
	return (0);
}

static int			do_work(int cs)
{
	int				r;
	char			buf[1024];
	int				ret;

	ret = 1;
	while (ret)
	{
		ft_bzero(buf, 1023);
		if ((r = read(cs, buf, 1023)) <= 0)
			continue;
		else
		{
			buf[r] = '\0';
			ret = do_command_line(cs, buf);
			send_confirmation(cs, ret);
		}
	}
	ft_bzero(buf, 1023);
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

static void			add_client(int sock)
{
	pid_t			pid;
	int				cs;

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
			close(cs);
			break ;
		}
		else if (pid > 0)
		{
			close(cs);
			continue;
		}
	}
}

int					main(int argc, char const *av[])
{
	int		port;
	int		sock;

	if (argc != 2)
		usage();
	port = ft_atoi(av[1]);
	if ((sock = create_server(port)) == -1)
		return (0);
	add_client(sock);
	close(sock);
	return (0);
}
