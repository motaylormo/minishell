/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:23:54 by mtaylor           #+#    #+#             */
/*   Updated: 2019/05/13 09:23:55 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*g_error_message[] = {
	[error_command] = "command not found",
	[error_env_var] = "environment variable missing",
	[error_no_arg] = "not enough arguments",
	[error_forking] = "forking error"
};

static void	print_error_message(const char *error, char *arg)
{
	ft_printf("minishell");
	if (error)
		ft_printf(": %s", error);
	if (arg)
		ft_printf(": %s", arg);
	ft_printf("\n");
}

void		handle_error(int errorcode, char *arg)
{
	if (errorcode == error_file)
	{
		if (access(arg, F_OK) != 0)
			print_error_message("no such file or directory", arg);
		else if (access(arg, X_OK) != 0)
			print_error_message("permission denied", arg);
	}
	else
		print_error_message(g_error_message[errorcode], arg);
}
