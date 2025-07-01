/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_handler_non_int.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:09:30 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 18:03:43 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

/**
 * This handler's only job is to print a newline to keep the
 * terminal clean after you interrupt a running command.
 * It should NOT call any readline functions.
 * 
 * We still set the flag for the exit code
 */
static void	ms_handle_sigint_non_interactive(int signum)
{
	(void) signum;
	g_signal = SIGINT;
}

/**
 * In this function we use simple handler for SIGINT
 * Set flags to 0
 * Keep ignoring SIGQUIT in the parent
 */
void	ms_signal_handlers_set_non_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_bzero(&sa_int, sizeof(sa_int));
	ft_bzero(&sa_quit, sizeof(sa_quit));
	sa_int.sa_handler = ms_handle_sigint_non_interactive;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("Minishell: Error setting non-interactive SIGINT handler");
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("Minishell: Error setting non-interactive SIGQUIT \
			handler");
}
