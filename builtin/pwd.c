/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:45:34 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/07/11 17:58:12 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#define TOO_MANY_ARGUMENTS		"too many arguments"
#define BAD_OPTION				"bad option" 
#define EXE_NAME				"pwd"

void	error_too_many_arguments()
{
	ft_putstr(EXE_NAME);
	ft_pustr(": ");
	ft_putstr(TOO_MANY_ARGUMENTS);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

void	error_bad_option(char param)
{
	ft_putstr(EXE_NAME);
	ft_putstr(": ");
	ft_putstr(BAD_OPTION);
	ft_putstr(": -");
	ft_putchar(param);
	ft_putchar('\n');
}

int		option(char *argument)
{
	int		is_physical;

	is_physical = FALSE;
	argument++;
	while (*argument != '\0')
	{
		if (*argument == 'L' && !is_physical)
			is_physical = FALSE;
		else if (*argument == 'P')
			is_physical = TRUE;
		else
			error_bad_option(*argument);
		argument++;
	}
}

void	pwd_symbolic(DIR *dir)
{
	if (dir->d_inno != 2)
	{
		ft_putchar('/');
		chdir("../");
		pwd_symbolic(dir);
	}
	else
		ft_putchar('\n');
	ft_putstr(dir->d_name);
}

void	pwd(int argc, char **argv)
{
	int		i;
	int		is_physical;
	char	buf[PATH_MAX + 1];
	DIR		*dir;

	option = FALSE;
	i = 1;
	while (i < argc)
	{
		if (*(argv[i]) != '-')
			error_too_many_arguments();
		else
			opt = opt | option(argv[i]);
		i++;
	}
	if (is_physical)
	{
		getcwd(buf, PATH_MAX);
		ft_putstr_endl(buf);
	}
	else
	{
		dir = opendir(".");
		pwd_symbolic(dir);
		closedir(dir);
	}
}
