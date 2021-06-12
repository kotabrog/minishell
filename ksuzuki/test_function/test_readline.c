/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:35:29 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/12 11:32:26 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(void)
{
	char *command;

	while (1)
	{
		command = readline("minishell ");
		if (command && strlen(command) > 0)
		{
			add_history(command);
			printf("%s\n", command);
		}
		else if (command == NULL)
		{
			printf("exit\n");
		}
		// 処理
		sleep(1);

		free(command);
	}
	return 0;
}
