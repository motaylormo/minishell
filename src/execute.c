/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:12:35 by mtaylor           #+#    #+#             */
/*   Updated: 2019/05/28 17:12:37 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Catch signals for the parent process and nullify them.
**	Let the signals do their thing in the child process.
*/

static void	sig_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
	signal(SIGINT, sig_handler);
}

void		run_executable(char *path, char **argv, char **envp)
{
	pid_t	process_id;

	if (access(path, X_OK) != 0)
		handle_error(error_file, path);
	else
	{
		process_id = fork();
		if (process_id < 0)
			handle_error(error_forking, NULL);
		else if (process_id == 0)
		{
			execve(path, argv, envp);
			exit(0);
		}
		else if (process_id > 0)
		{
			signal(SIGINT, sig_handler);
			wait(&process_id);
		}
	}
	ft_matrixdel(&envp);
}
