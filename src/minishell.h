/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:06:36 by mtaylor           #+#    #+#             */
/*   Updated: 2019/05/13 09:06:37 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
**	ALLOWED FUNCTIONS
**	  <stdlib.h>	malloc() & free()
**					& exit()
**	   <fcntl.h>	open()
**	  <unistd.h>	access()
**					& close()
**					& read() & write()
**					& getcwd() & chdir()
**					& fork() & execve()
**	  <dirent.h>	opendir() & readdir() & closedir()
**	<sys/stat.h>	stat() & lstat() & fstat()
**	<sys/wait.h>	wait() & waitpid() & wait3() & wait4()
**	  <signal.h>	signal() & kill()
**
**	FOR MACROS
**	  <limits.h>	PATH_MAX
**
**	FOR BONUSES
**	 <termcap.h>	tgetent() & tgetstr() & tgoto()
**	     <pwd.h>	getpwuid()
*/
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <termcap.h>
# include <pwd.h>

/*
**	Colors for the prompt
*/
# define COLOR1 CYAN
# define COLOR2 I_BLUE
# define COLOR_TRIM I_CYAN

# define PROMPT	COLOR1 "ᴍɪɴɪ" COLOR2 "sʜᴇʟʟ" COLOR1 ">"

/*
**	Data struct for storing env
*/
typedef struct s_node	t_node;
struct	s_node{
	t_node	*next;
	char	label[PATH_MAX + 1];
	char	data[PATH_MAX + 1];
};

typedef struct s_queue	t_queue;
struct	s_queue{
	t_node	*first;
	t_node	*last;
};

/*
**	no flags	default prompt
**	-p			pwd prompt
*/
int	g_flags;

enum	e_flags{
	flag_path = 1 << 0
};

enum	e_errors{
	error_file,
	error_command,
	error_env_var,
	error_no_arg,
	error_forking
};

void	handle_error(int errorcode, char *arg);
void	run_shell(t_queue *q);
void	run_executable(char *path, char **argv, char **envp);
void	print_prompt(void);
void	builtin_echo(t_queue *q, char **av);
void	builtin_cd(t_queue *q, char **av);
void	builtin_exit(t_queue *q, char **av);
void	builtin_env(t_queue *q, char **av);
void	builtin_setenv(t_queue *q, char **av);
void	builtin_unsetenv(t_queue *q, char **av);
int		enqueue_env(t_queue *q, char *str);
char	*find_node(t_queue *q, char *label);
char	**queue_to_strvector(t_queue *q);

#endif
