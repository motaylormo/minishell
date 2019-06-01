/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:43:40 by mtaylor           #+#    #+#             */
/*   Updated: 2019/05/13 12:43:41 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	enqueue(t_queue *q, t_node *n)
{
	if (!n)
		return ;
	n->next = NULL;
	if (q->first == NULL)
	{
		q->first = n;
		q->last = n;
	}
	else
	{
		q->last->next = n;
		q->last = q->last->next;
	}
}

int			enqueue_env(t_queue *q, char *str)
{
	t_node	*n;
	int		eq_index;

	if ((eq_index = ft_strchrindex(str, '=')) != -1)
	{
		n = ft_memalloc(sizeof(t_node));
		ft_strncpy(n->label, str, eq_index);
		ft_strcpy(n->data, str + eq_index + 1);
		enqueue(q, n);
		return (1);
	}
	return (0);
}

char		*find_node(t_queue *q, char *label)
{
	t_node	*n;

	n = q->first;
	while (n)
	{
		if (ft_strequ(n->label, label))
			return (n->data);
		n = n->next;
	}
	return (NULL);
}

char		**queue_to_strvector(t_queue *q)
{
	char	**envp;
	int		count;
	char	temp[PATH_MAX + 1];
	t_node	*n;
	int		i;

	count = 0;
	n = q->first;
	while (n)
	{
		count++;
		n = n->next;
	}
	envp = ft_memalloc(sizeof(char*) * (count + 1));
	i = 0;
	n = q->first;
	while (n)
	{
		ft_strcpy(temp, n->label);
		ft_strcat(temp, "=");
		ft_strcat(temp, n->data);
		envp[i++] = ft_strdup(temp);
		n = n->next;
	}
	return (envp);
}
