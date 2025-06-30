/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:50:27 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 11:43:56 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

static void ms_handle_sigint_heredoc(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

void ms_signal_handlers_set_heredoc(void)
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = ms_handle_sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
}
