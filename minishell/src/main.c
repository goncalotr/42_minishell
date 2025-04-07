/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:22:18 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/07 16:47:46 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Definition of the global variable
int	g_last_exit_status = 0;

/**
 * @brief The main interactive loop of the minishell.
 *
 * Reads input using readline, adds it to history, checks for "exit",
 * and prepares for parsing/execution (currently just prints input).
 * Handles EOF (Ctrl+D).
 * 
 * 1. Read input with prompt
 * 2. Handle EOF (CTRL+D)
 * 3. Handle empty input (Enter)
 * 4. Add non-empty input to history
 * 5. Check for exit command
 * 6. Placeholder for parsing
 * 7. Free input line
 */
void	ms_core_loop(void)
{
	char	*input_line;

	while (1)
	{
		input_line = readline(BLUE "minishell> " RESET);
		if (input_line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (input_line[0] == '\0')
		{
			free(input_line);
			continue;
		}
		add_history(input_line);
		if(strcmp(input_line, "exit")==0)
		{
			free(input_line);
			break;
		}
		ft_printf(YELLOW "DEBUG Received command: <%s>\n" RESET, input_line);
		free(input_line);
		input_line = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	// TODO: Initialize environment variables list from envp
	// TODO: Initialize signal handlers (SIGINT, SIGQUIT)

	ms_signal_handlers_init();


	printf(GREEN "DEBUG Welcome to Minishell!\n---\n" RESET "\n");

	ms_core_loop();

	//TODO Cleanup

	printf(RED "\n---\nDEBUG Exiting Minishell. Final status: %d" RESET "\n", g_last_exit_status);

	return (g_last_exit_status);
}
