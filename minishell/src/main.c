/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:22:18 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/02 15:22:24 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Definition of the global variable
extern unsigned char	g_signal;

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
 * 
 * 
 */
static void	ms_core_loop(t_minishell *data)
{
	char	*input_line;
	char	**args;
	char	*prompt_str;
	int		saved_errno;

	g_signal = 0;
	while (1)
	{
		data->last_exit_status = g_signal;
		if (g_signal == 130)
		{
			g_signal = 0;
		}
		prompt_str = ms_get_prompt(data);
		if (!prompt_str)
		{
			ft_putstr_fd("Critical error: Could not generate prompt. \
			Exiting.\n", 2);
			break ;
		}
		input_line = readline(prompt_str);
		if (g_signal == 130)
		{
			saved_errno = errno;
			ft_printf(YELLOW "DEBUG SIGINT detected! errno=%d (%s)\n" \
			RESET, saved_errno, strerror(saved_errno));
			if (input_line)
			{
				free(input_line);
				data->last_exit_status = 130;
			}
			continue ;
		}
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
		ms_syntax_check(input_line);
		if (!args)
		{
			free(input_line);
			g_signal = 1;
			continue ;
		}
		ms_expand_variables(args, data->last_exit_status);
		ms_debug_print_args(args);
		g_signal = ms_execute_command_placeholder(args, data);
		ms_debug_print_gsig();
		ms_free_split_args(args);
		free(input_line);
		input_line = NULL;
	}
}

/**
 * shell _data is the main struct created on the stack
 */
int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell_data;

	(void) argc;
	(void) argv;
	if (init_shell_data(&shell_data, argv, envp) != 0)
		return (EXIT_FAILURE);
	ms_signal_handlers_init();
	printf(GREEN "DEBUG Minishell Start!\n---\n" RESET "\n");
	ms_core_loop(&shell_data);
	printf(RED "\n---\nDEBUG Exiting Minishell. Final status: %d" RESET "\n", \
		g_signal);
	return (g_signal);
}
