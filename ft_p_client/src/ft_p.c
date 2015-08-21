/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 14:49:00 by larry             #+#    #+#             */
/*   Updated: 2015/08/21 16:23:39 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void			usage()
{
	ft_putstr("Usage : ./server <ip> <port>\n");
	exit(-1);
}

static int			create_client(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("connect error.\n");
		exit(EXIT_FAILURE);
	}
	return (sock);
}

static char*			prompt(int sock)
{
	char			*request;
	char			request_ori[1024];

	request = NULL;
	ft_bzero(request_ori, 1023);
	ft_putstr("ft_p (client) ?>");
	read(0, request_ori, 1023);
	ft_bzero(request, ft_strlen(request));
	request = ft_strtrim(request_ori);
   	if (!(write(sock, request, ft_strlen(request))))
   		return (NULL);
   	ft_bzero(request_ori, 1023);
   	return (request);
}

static int			do_commande_line(int sock, char **argv)
{
	if (ft_strcmp(argv[0], "ls") == 0)
		return (option_ls(sock));
	if (ft_strcmp(argv[0], "quit") == 0)
		return (1);
	return (0);
}

static int			do_work(int sock)
{
	char			*request;
	char			**argv;

	while (1)
	{
		if (!(request = prompt(sock)))
			exit(EXIT_FAILURE);

		argv = ft_strsplit(request, ' ');
		if (!do_commande_line(sock, argv))
		{
			ft_putstr("ft_p : ");
			ft_putstr(argv[0]);
			ft_putstr(" : commande unkown\n");
   		}

   		if (ft_strstr(request, "quit"))
   				break;

   		free(request);
   		free(argv);
   	}
   	if ((write(sock, "\x2\0", 2) < 0))
		exit(EXIT_FAILURE);
	return (0);
}

int					main(int argc, char const *av[])
{
	int		port;
	int		sock;

	if (argc != 3)
		usage();
	port = ft_atoi(av[2]);
	sock = create_client((char *)av[1], port);
	do_work(sock);
	ft_putstr("ft_p : Client was disconnected\n");
	close(sock);
	return (0);
}
