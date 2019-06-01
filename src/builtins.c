/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:28:17 by mtaylor           #+#    #+#             */
/*   Updated: 2019/05/13 10:28:18 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_echo(t_queue *q, char **av)
{
	int	i;

	(void)q;
	i = 0;
	while (av[++i])
	{
		ft_printf("%s", av[i]);
		if (av[i + 1])
			ft_printf("%c", ' ');
	}
	ft_printf("\n");
}

/*
**	cd -	oldpwd
**	cd		home
*/

static int	get_cd_path(t_queue *q, char *arg, char *path)
{
	char	*env_var;
	char	*data_ptr;

	env_var = NULL;
	if (!arg)
		env_var = "HOME";
	else if (ft_strequ(arg, "-"))
		env_var = "OLDPWD";
	if (env_var)
	{
		if ((data_ptr = find_node(q, env_var)))
			ft_strcpy(path, data_ptr);
		else
		{
			handle_error(error_env_var, env_var);
			return (0);
		}
	}
	else
		ft_strcpy(path, arg);
	return (1);
}

void		builtin_cd(t_queue *q, char **av)
{
	char	*pwd;
	char	*oldpwd;
	char	path[PATH_MAX + 1];

	if (!(pwd = find_node(q, "PWD")))
	{
		enqueue_env(q, "PWD=");
		pwd = q->last->data;
		getcwd(pwd, PATH_MAX);
	}
	if (!(get_cd_path(q, av[1], path)))
		return ;
	if (chdir(path) == -1)
		return (handle_error(error_file, path));
	if ((oldpwd = find_node(q, "OLDPWD")))
		ft_strcpy(oldpwd, pwd);
	getcwd(pwd, PATH_MAX);
}

void		builtin_exit(t_queue *q, char **av)
{
	ft_matrixdel(&av);
	(void)q;
	exit(0);
}
