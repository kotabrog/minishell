#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_status *status;
	char *command1;
	char *command2;

	command1 = "export";
	command2 = "SHLVL=3";
	status = malloc(sizeof(t_status));
	status->command = malloc(sizeof(t_command));
	status->command->command = malloc(sizeof(char *) * 2);
	status->command->command[0] = ft_strdup(command1);
	status->command->command[1] = ft_strdup(command2);

	env_init(status, env);
	do_env(status->env);
	write(1, "========changed=======", 20);
	do_export(status->command->command, status->env);
	do_env(status->env);

	return (0);

}