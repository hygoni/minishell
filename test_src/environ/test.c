#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "ft_environ.h"

int		main(int argc, char **argv, char **env)
{
	char	**new_env;
	int		len;
	int		idx;

	idx = 0;
	while (env[idx] != 0)
	{
		printf("%s\n", env[idx]);
		idx++;
	}
	len = get_strarr_size(env);
	printf("main env size: %d\n", len);
	new_env = cpy_env(env, len);
	idx = 0;
	printf("========environ========\n");
	while (new_env[idx] != 0)
	{
		printf("%s\n", new_env[idx]);
		idx++;
	}
	printf("========environ========\n");
	printf("cpy env success\n");
	argc--;
	argv++;
	builtin_export(argc, argv, &new_env);
	printf("export success\n");
	idx = 0;
	len = get_strarr_size(new_env);
	printf("cpy env size: %d\n", len);
	while (idx < len)
	{
		printf("%s\n", new_env[idx]);
		idx++;
	}
}
