/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:20:12 by mtaylor           #+#    #+#             */
/*   Updated: 2019/05/13 09:20:14 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		parse_flags(int argc, char **argv)
{
	int	c;

	g_flags = 0;
	while ((c = ft_getopt(argc, argv, "p")) != -1)
	{
		if (c == 'p')
			g_flags |= flag_path;
	}
}

static t_queue	*envp_to_queue(char **envp)
{
	t_queue	*q;
	char	*tmp;
	int		i;

	q = ft_memalloc(sizeof(t_queue));
	i = -1;
	while (envp[++i])
	{
		enqueue_env(q, envp[i]);
		if (q->last && ft_strequ(q->last->label, "SHLVL"))
		{
			tmp = ft_itoa(ft_atoi(q->last->data) + 1);
			ft_strcpy(q->last->data, tmp);
			ft_strdel(&tmp);
		}
	}
	return (q);
}

static void		termcaps_delete(int n)
{
	char	bp[1024];
	char	buf[30];
	char	*area;
	char	*del_char;
	char	*backspace;

	tgetent(bp, getenv("TERM"));
	area = buf;
	del_char = tgetstr("dc", &area);
	backspace = tgetstr("kb", &area);
	ft_putstr(tgetstr("dm", &area));
	while (n--)
	{
		ft_putstr(tgoto(backspace, 0, 0));
		ft_putstr(del_char);
	}
	ft_putstr(tgetstr("ed", &area));
}

/*
**	Termcaps deletes the last 2 characters ("^C")
**		then newline and fresh prompt
*/

static void		sigint_handler(int sig)
{
	(void)sig;
	termcaps_delete(ft_strlen("^C"));
	ft_printf("\n");
	print_prompt();
	signal(SIGINT, sigint_handler);
}

int				main(int argc, char **argv, char **envp)
{
	t_queue	*q;

	parse_flags(argc, argv);
	q = envp_to_queue(envp);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		run_shell(q);
	}
}
