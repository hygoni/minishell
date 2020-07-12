#include <unistd.h>
#include <stdlib.h>
#include "environ.h"

void			free_string_arr(char **arg)
{
	int		idx;
	int		len;


	len = get_strarr_size(arg);
	idx = 0;
	while (idx < len)
	{
		free(arg[idx]);
		idx++;
	}
	free(arg);
}

void			clean_arg(char *key, char *value, char **arg, char **env)
{
	int		idx;
	int		len;

	if (key != 0)
		free(key);
	if (value != 0)
		free(value);
	if (arg != 0)
		free_string_arr(arg);
	if (env != 0)
		free_string_arr(arg);
	exit(1);
}
