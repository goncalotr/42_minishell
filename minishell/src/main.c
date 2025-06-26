/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:22:18 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/26 13:31:15 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Definition of the global variable
//extern unsigned char	g_signal;
volatile sig_atomic_t g_signal;

/**
 * @brief The main interactive loop of the minishell.
 *
 * Reads input using readline, adds it to history, checks for "exit",
 * and prepares for parsing/execution (currently just prints input).
 * Handles EOF (Ctrl+D).
 * 
 * 1. Read input with prompt
 * 2. Handle EOF (CTRL+D) - input_line == NULL
 * 3. Handle empty input (Enter)
 * 4. Add non-empty input to history
 * 5. Check for exit command
 * 6. Placeholder for parsing
 * 7. Free input line
 * 
 * SIGINT = 130
 * isatty checks if the shell is runningin an interactive terminal
 */
static void	ms_core_loop(t_minishell *data)
{
	char	*input_line;
	//char	**args;
	char	*prompt_str;
	//int		saved_errno;

	while (1)
	{
		if (g_signal == SIGINT)
		{
			data->last_exit_status = 130;
			g_signal = 0;
		}
		ms_signal_handlers_set_interactive();
		prompt_str = ms_get_prompt(data);
		if (!prompt_str)
		{
			ft_putstr_fd("Minishell: Critical error generating prompt. \
			Exiting.\n", 2);
			break ;
		}
		input_line = readline(prompt_str);
		free(prompt_str);
		if (g_signal == SIGINT)
		{
			data->last_exit_status = 130;
			g_signal = 0;
		}
		// 2. Handle readline's return value
		if (input_line == NULL)
			ms_exit_shell_sig(data, data->last_exit_status);
		// 3. Handle empty input line (user pressed Enter)
		if (input_line[0] == '\0')
		{
			//tcsetattr(STDIN_FILENO, TCSAFLUSH, original_termios); 
			data->last_exit_status = 0;
			free(input_line);
			continue ;
		}
		add_history(input_line);
		// --- Syntax check ---
		// ft_printf(YELLOW "DEBUG Received: <%s>\n" RESET, input_line);
		//args = ms_parse_input_placeholder(input_line);
		if (ms_syntax_check(input_line))
		{
			data->last_exit_status = 2; //or 258? 2 for syntax errors
			free(input_line);
			continue ;
		}
		// --- PARSING AND EXECUTION ---
		ms_main_parsing(input_line, data);
		free(input_line);
	}
	rl_clear_history();
	ms_cleanup_shell(data);
}

/**
 * shell _data is the main struct created on the stack
 */
int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell_data;
	//struct termios	original_termios;

	(void) argc;
	(void) argv;
	g_signal = 0;
	if (init_shell_data(&shell_data, argv, envp) != 0)
		return (EXIT_FAILURE);
	//ms_signal_handlers_init();
	//ms_signal_handlers_set_interactive();
	printf(GREEN "DEBUG Minishell Start!\n---\n" RESET "\n");
	//tcgetattr(STDIN_FILENO, &original_termios); 
	ms_core_loop(&shell_data);
	printf(RED "\n---\nDEBUG Exiting Minishell. Final status: %d" RESET "\n", \
		g_signal);
	//return (g_signal);
	return(shell_data.last_exit_status);
}
