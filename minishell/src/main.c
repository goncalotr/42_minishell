/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:22:18 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/16 12:36:16 by goteixei         ###   ########.fr       */
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
void	ms_core_loop(char **envp, t_data *data)
{
	char	*input_line;
	char	**args;

	while (1)
	{
		input_line = readline(BLUE "minishell> " RESET);
		if (input_line == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		if (input_line[0] == '\0')
		{
			free(input_line);
			continue ;
		}
		add_history(input_line);
		ft_printf(YELLOW "DEBUG Received: <%s>\n" RESET, input_line);
		args = ms_parse_input_placeholder(input_line);
		if (!args)
		{
			free(input_line);
			g_last_exit_status = 1;
			continue;
		}
		ms_debug_print_args(args);
		g_last_exit_status = ms_execute_command_placeholder(args, envp, data);
		ms_free_split_args(args);
		free(input_line);
		input_line = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//(void)envp;
	t_data	shell_data; // Create an instance of the struct (on the stack)

	if (init_shell_data(&shell_data, argv, envp) != 0)
	{
		return (EXIT_FAILURE);
	}
	ms_signal_handlers_init();
	// TODO: Initialize environment variables list from envp
	printf(GREEN "DEBUG Welcome to Minishell!\n---\n" RESET "\n");
	ms_core_loop(envp, &shell_data);
	//TODO Cleanup
	printf(RED "\n---\nDEBUG Exiting Minishell. Final status: %d" RESET "\n", \
		g_last_exit_status);
	return (g_last_exit_status);
}
