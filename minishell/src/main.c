/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:22:18 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/01 11:11:14 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Definition of the global variable
//extern unsigned char	g_signal;
volatile sig_atomic_t	g_signal;

static void	ms_execute_command_line(char *input_line, t_minishell *data)
{
	add_history(input_line);
	if (ms_syntax_check(input_line))
	{
		input_line = ms_remove_whitespaces(input_line);
		if (!input_line)
			data->last_exit_status = 0;
		else
			data->last_exit_status = 2;
		free(input_line);
		return ;
	}
	ms_main_parsing(input_line, data);
	free(input_line);
}

static void	ms_reset_signal_state(t_minishell *data)
{
	if (g_signal == SIGINT)
	{
		data->last_exit_status = 130;
		g_signal = 0;
	}
}

static char	*ms_read_user_input(t_minishell *data)
{
	char	*prompt_str;
	char	*input_line;

	ms_reset_signal_state(data);
	ms_signal_handlers_set_interactive();
	prompt_str = ms_get_prompt(data);
	if (!prompt_str)
	{
		ft_putstr_fd("Minishell: Critical prompt error. Exiting.\n", 2);
		ms_exit_shell(data, 1);
	}
	input_line = readline(prompt_str);
	free(prompt_str);
	ms_reset_signal_state(data);
	return (input_line);
}

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
 * isatty checks if the shell is running in an interactive terminal
 */
static void	ms_core_loop(t_minishell *data)
{
	char	*input_line;

	while (1)
	{
		input_line = ms_read_user_input(data);
		if (input_line == NULL)
			ms_exit_shell_sig(data, data->last_exit_status);
		if (input_line[0] == '\0')
		{
			data->last_exit_status = 0;
			free(input_line);
			continue ;
		}
		ms_execute_command_line(input_line, data);
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
	signal(SIGPIPE, SIG_IGN);
	g_signal = 0;
	if (init_shell_data(&shell_data, argv, envp) != 0)
		return (EXIT_FAILURE);
	ms_core_loop(&shell_data);
	return (shell_data.last_exit_status);
}
