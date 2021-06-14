#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_status *status;

	status = (t_status *)malloc(sizeof(t_status));

	env_init(status, env);
	do_env(status->env);

	return (0);

}