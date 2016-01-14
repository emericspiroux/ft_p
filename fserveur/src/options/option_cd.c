/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 19:13:05 by larry             #+#    #+#             */
/*   Updated: 2016/01/13 19:06:54 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void				cd_minus(char *last_dir)
{
	char				tmp_dir[PATH_MAX];

	ft_putstr(last_dir);
	ft_putstr("\n");
	getcwd(tmp_dir, sizeof(tmp_dir));
	chdir(last_dir);
	ft_bzero(last_dir, PATH_MAX);
	ft_strcpy(last_dir, tmp_dir);
	ft_bzero(tmp_dir, PATH_MAX);
}

static int				cd_path(char *path, char *last_dir)
{
	if (is_autorized("cd", path, 0))
	{
		getcwd(last_dir, sizeof(last_dir));
		chdir(path);
		return (0);
	}
	return (1);
}

static int				do_cd(int argc, char *path)
{
	static char			last_dir[PATH_MAX] = "\0";
	static char			base_path[PATH_MAX] = "\0";

	if (ft_strlen(base_path) <= 0)
		getcwd(base_path, sizeof(base_path));
	if (argc == 2)
	{
		if (ft_strlen(last_dir) == 0)
			ft_strcpy(last_dir, base_path);
		if (ft_strcmp(path, "-") == 0)
			cd_minus(last_dir);
		else if (ft_strcmp(path, "~") == 0)
			return (cd_path(base_path, last_dir));
		else
			return (cd_path(path, last_dir));
	}
	else
		return (cd_path(base_path, last_dir));
	return (0);
}

int						option_cd(int cs, int argc, char **argv)
{
	int					resp;
	struct s_stdout		fd_save;

	fd_save = redirect_stdout(cs);
	resp = 0;
	errno = 0;
	if (argc <= 2)
		resp = do_cd(argc, argv[1]);
	else
	{
		ft_putstr("cd: string not in pwd : ");
		ft_putstr(argv[1]);
		ft_putstr("\n");
		resp = 1;
	}
	close_redirect_stdout(fd_save);
	errno = 0;
	send_confirmation(cs, resp);
	return (0);
}
