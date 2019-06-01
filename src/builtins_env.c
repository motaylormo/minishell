/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:28:17 by mtaylor           #+#    #+#             */
/*   Updated: 2019/05/13 10:28:18 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_queue *q, char **av)
{
	t_node	*n;

	(void)av;
	n = q->first;
	while (n)
	{
		ft_printf("%s=%s\n", n->label, n->data);
		n = n->next;
	}
}

void	builtin_setenv(t_queue *q, char **av)
{
	char	*label[2];

	if (!av[1])
		return (handle_error(error_no_arg, NULL));
	if (enqueue_env(q, av[1]))
	{
		if (find_node(q, q->last->label) != q->last->data)
		{
			label[1] = q->last->label;
			builtin_unsetenv(q, label);
		}
	}
}

void	builtin_unsetenv(t_queue *q, char **av)
{
	t_node	*n;
	t_node	*prev;

	if (!av[1])
		return (handle_error(error_no_arg, NULL));
	n = q->first;
	prev = NULL;
	while (n)
	{
		if (ft_strequ(n->label, av[1]))
		{
			if (prev)
				prev->next = n->next;
			if (n == q->first)
				q->first = n->next;
			if (n == q->last)
				q->last = prev;
			free(n);
			return ;
		}
		prev = n;
		n = n->next;
	}
	handle_error(error_env_var, av[1]);
}
