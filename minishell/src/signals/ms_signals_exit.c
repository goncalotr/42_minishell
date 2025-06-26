/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:15:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/26 13:17:21 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

/**
 * function for ctrl d
 * 
 * exit - ms_cleanup_shell
 * ctrl d - ms_cleanup_shell(data)
 */
void	ms_exit_shell_sig(t_minishell *data, int exit_code)
{
	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
	}
	ms_cleanup_shell(data);
	clear_history();
	exit(exit_code);
}
