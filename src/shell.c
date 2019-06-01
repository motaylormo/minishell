/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:56:06 by mtaylor           #+#    #+#             */
/*   Updated: 2019/05/16 15:56:10 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*g_builtin_str[] = {
	"echo",
	"cd",
	"setenv",
	"unsetenv",
	"env",
	"exit",
	(NULL)
};

static void			(*g_builtin_func[])(t_queue*, char**) =
{
	builtin_echo,
	builtin_cd,
	builtin_setenv,
	builtin_unsetenv,
	builtin_env,
	builtin_exit
};

static int	path(t_queue *q, char **av)
{
	char	**path_arr;
	char	exec_path[PATH_MAX + 1];
	int		i;

	if (!(path_arr = ft_strsplit(find_node(q, "PATH"), ':')))
		return (0);
	i = -1;
	while (path_arr[++i])
	{
		ft_cpycat_path(exec_path, path_arr[i], av[0]);
		if (access(exec_path, F_OK) == 0)
		{
			run_executable(exec_path, av, queue_to_strvector(q));
			ft_matrixdel(&path_arr);
			return (1);
		}
	}
	ft_matrixdel(&path_arr);
	return (0);
}

static void	execute_command(t_queue *q, char **av)
{
	int	i;

	i = -1;
	while (g_builtin_str[++i])
	{
		if (ft_strequ(av[0], g_builtin_str[i]))
			return ((*g_builtin_func[i])(q, av));
	}
	if (path(q, av))
		return ;
	if (access(av[0], F_OK) == 0)
		return (run_executable(av[0], av, queue_to_strvector(q)));
	handle_error(error_command, av[0]);
}

static char	**expansions_in_args(t_queue *q, char **av)
{
	char	*label;
	char	*node_ptr;
	char	*new_str;
	int		i;

	i = -1;
	while (av[++i])
	{
		if (av[i][0] == '~' || av[i][0] == '$')
		{
			label = (av[i][0] == '~') ? "HOME" : av[i] + 1;
			if (!(node_ptr = find_node(q, label)))
				handle_error(error_env_var, label);
			else
			{
				if (av[i][0] == '~')
					new_str = ft_strjoin(node_ptr, av[i] + 1);
				else
					new_str = ft_strdup(node_ptr);
				ft_strdel(&av[i]);
				av[i] = new_str;
			}
		}
	}
	return (av);
}

/*
**	The if around get_next_line() is to exit on ctrl + d
*/

void		run_shell(t_queue *q)
{
	char	*line;
	char	**semicolon_split;
	char	**av;
	int		i;

	print_prompt();
	line = NULL;
	if (get_next_line(0, &line) < 1)
		exit(0);
	semicolon_split = ft_strsplit(line, ';');
	i = -1;
	while (semicolon_split[++i])
	{
		if ((av = str_to_argv(semicolon_split[i])))
		{
			av = expansions_in_args(q, av);
			execute_command(q, av);
		}
		ft_matrixdel(&av);
	}
	ft_matrixdel(&semicolon_split);
	ft_strdel(&line);
}
