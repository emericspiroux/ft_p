/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 19:13:05 by larry             #+#    #+#             */
/*   Updated: 2015/08/26 02:19:06 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void		open_dir_error(char *arg)
{
	ft_putstr("ft_p: cd : ");
	if (errno == EACCES)
		ft_putstr("Permission denied.");
	if (errno == EBADF)
		ft_putstr("file descriptor is not a valid for reading.");
	if (errno == EMFILE)
		ft_putstr("Too many file descriptors in use by process.");
	if (errno == ENFILE)
		ft_putstr("Too many files are currently open in the system.");
	if (errno == ENOENT)
		ft_putstr("Directory does not exist, or is empty string");
	if (errno == ENOMEM)
		ft_putstr("Insufficient memory to complete the operation");
	if (errno == ENOTDIR)
	{
		ft_putstr(arg);
		ft_putstr(" is not a directory.");
	}
	ft_putstr("\n");
}

int				option_cd(int cs, int argc, char **argv)
{
	int			resp;
	int			oldfd;
	int			fnode;
	int			asknode;
	static char	last_dir[PATH_MAX] = "\0";
	char		tmp_dir[PATH_MAX];

	oldfd = dup(cs);
	dup2(oldfd, 1);
	dup2(oldfd, 2);
	resp = 0;
	errno = 0;
	if (ft_strlen(last_dir) == 0)
		ft_strcpy(last_dir, "/Users/larry/Dropbox/Codetoborn/ft_p_git2/ft_p_server\0");
	if (argc < 3)
	{
		if (ft_strcmp(argv[1], "-") == 0)
		{
			ft_putstr(last_dir);
			ft_putstr("\n");
			getcwd(tmp_dir, sizeof(tmp_dir));
			chdir(last_dir);
			ft_bzero(last_dir, PATH_MAX);
			ft_strcpy(last_dir, tmp_dir);
			ft_bzero(tmp_dir, PATH_MAX);
		}
		else
		{
			fnode = autorized_folder(0);
			if ((asknode = ft_getInode(argv[1])) == -1)
			{
				open_dir_error(argv[1]);
				resp = 1;
			}
			if (asknode < fnode)
			{
				ft_putstr("ft_p: cd : Permission denied by server.\n");
				resp = 1;
			}
			else
			{
				getcwd(last_dir, sizeof(last_dir));
				chdir(argv[1]);
			}
		}
	}
	else
	{
		ft_putstr("cd: string not in pwd : ");
		ft_putstr(argv[1]);
		ft_putstr("\n");
		resp = 1;
	}
	close(oldfd);
	errno = 0;
	send_confirmation(cs, resp);
	return (0);
}
