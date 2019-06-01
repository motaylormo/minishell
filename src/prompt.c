/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stylistic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:17:31 by mtaylor           #+#    #+#             */
/*   Updated: 2019/05/13 18:17:32 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*g_small_caps[] = {
	['a'] = "ᴀ",
	['b'] = "ʙ",
	['c'] = "ᴄ",
	['d'] = "ᴅ",
	['e'] = "ᴇ",
	['f'] = "ғ",
	['g'] = "ɢ",
	['h'] = "ʜ",
	['i'] = "ɪ",
	['j'] = "ᴊ",
	['k'] = "ᴋ",
	['l'] = "ʟ",
	['m'] = "ᴍ",
	['n'] = "ɴ",
	['o'] = "ᴏ",
	['p'] = "ᴘ",
	['q'] = "ǫ",
	['r'] = "ʀ",
	['s'] = "s",
	['t'] = "ᴛ",
	['u'] = "ᴜ",
	['v'] = "ᴠ",
	['w'] = "ᴡ",
	['x'] = "x",
	['y'] = "ʏ",
	['z'] = "ᴢ"
};

static void	print_small_caps(char c)
{
	if (ft_isalpha(c))
		ft_printf("%s", g_small_caps[ft_tolower(c)]);
	else
		ft_printf("%c", c);
}

static void	pwd_prompt(void)
{
	char			pwd[PATH_MAX + 1];
	struct passwd	*passwd;
	int				color;
	int				i;

	getcwd(pwd, PATH_MAX);
	i = -1;
	if ((passwd = getpwuid(getuid())) &&
		ft_strnequ(passwd->pw_dir, pwd, ft_strlen(passwd->pw_dir)))
	{
		i = ft_strlen(passwd->pw_dir) - 1;
		ft_printf(COLOR_TRIM "~");
	}
	color = 0;
	while (pwd[++i])
	{
		if (pwd[i] == '/')
		{
			ft_printf(COLOR_TRIM " | ");
			color = (color == 1) ? 0 : 1;
			ft_printf((color == 1) ? COLOR2 : COLOR1);
		}
		else
			print_small_caps(pwd[i]);
	}
}

void		print_prompt(void)
{
	if (g_flags & flag_path)
		pwd_prompt();
	else
		ft_printf(PROMPT);
	ft_printf(COLOR_OFF " ");
}
