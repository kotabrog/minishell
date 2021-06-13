/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:35:29 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/13 15:34:06 by ksuzuki          ###   ########.fr       */
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
		// sleep(1);
		// printf("rl_point: %d\n", rl_point);
		// printf("rl_end: %d\n", rl_end);
		// printf("rl_mark: %d\n", rl_mark);
		// printf("rl_done: %d\n", rl_done);
		// printf("rl_num_chars_to_read: %d\n", rl_num_chars_to_read);
		// printf("rl_signal_event_hook: %p\n", rl_signal_event_hook);
		printf("\033[1Chello\n");
		printf("\033[10Chello\n");
		printf("\033[50Chello\n");
		printf("\033[100Chello\n");
		printf("\033[200Chello\n");
		printf("\033[300Chello\n");
		printf("\033[400Chello\n");
		printf("%d\n", rl_catch_signals);
		free(command);
	}
	return 0;
}
