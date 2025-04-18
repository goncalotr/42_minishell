/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:37:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 18:50:21 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

unsigned char	g_signal;

/**
 * @brief Signal handler for SIGINT (Ctrl+C) in interactive mode.
 *
 * Action: Prints a newline, clears the current readline buffer,
 * redisplays the prompt, and sets the global exit status.
 * Based on readline's recommended way to handle signals.
 * @param sig The signal number (unused but required by signature).
 * 
 * rl_on_new_line, rl_replace_line, rl_redisplay are included in
 * readline/readline.h
 * 128 + sigint
 * 
 * 	//ft_putstr_fd("\n", STDOUT_FILENO);
 */
static void	ms_handle_sigint_init(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Sets up the signal handlers for the main interactive loop.
 *
 * Configures SIGINT (Ctrl+C) to call handle_sigint_interactive.
 * Configures SIGQUIT (Ctrl+\) to be ignored (SIG_IGN).
 * Uses sigaction for more reliable signal handling.
 */
void	ms_signal_handlers_init(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = ms_handle_sigint_init;
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("Error setting SIGINT handler");
		exit(EXIT_FAILURE);
	}
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("Error setting SIGQUIT handler");
		exit(EXIT_FAILURE);
	}
}
