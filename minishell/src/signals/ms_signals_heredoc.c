/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:50:27 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/27 10:51:00 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

static void ms_handle_sigint_heredoc(int signum)
{
	(void)signum;
	// Set the global signal flag to indicate an interruption.
	g_signal = SIGINT;
	// Close standard input. This will cause the read() or get_next_line()
	// in the heredoc loop to fail, breaking the loop.
	close(STDIN_FILENO);
}

void ms_signal_handlers_set_heredoc(void)
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = ms_handle_sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
}
