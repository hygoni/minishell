#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "ft_environ.h"

int		main(int argc, char **argv, char **env)
{
	char	**new_env;
	int		len;

	len = get_strarr_size(env);
	printf("main env size: %d\n", len);
	new_env = cpy_env(env, len);
	printf("========environ========\n");
	builtin_env(new_env);
	printf("========environ========\n");
	printf("cpy env success\n");

	argc--;
	argv++;
	builtin_export(argc, argv, &new_env);
	printf("export success\n");
	len = get_strarr_size(new_env);
	printf("cpy env size: %d\n", len);
	printf("========export start========\n");
	builtin_env(new_env);
	printf("========export end========\n");
	builtin_unset(argc, argv, &new_env);
	printf("========unset start========\n");
	builtin_env(new_env);
	printf("========unset end========\n");

}
