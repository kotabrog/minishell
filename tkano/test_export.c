#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_status *status;
	char *command;

	command = "export";
	status = malloc(sizeof(t_status));
	status->command = malloc(sizeof(t_command));
	status->command->command = malloc(sizeof(char *) * 2);
	status->command->command[0] = ft_strdup(command);
	status->command->command[1] = ft_strdup(command);

	env_init(status, env);
	do_env(status->env);
	do_export(status->command->command, status->env);

	return (0);

}