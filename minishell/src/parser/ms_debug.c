/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:42:08 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/16 11:44:10 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Prints the command and its arguments individually for debugging.
 *
 * @param context A string describing the context (e.g., "Parsed Arguments").
 * @param args The NULL-terminated array of strings (command and args).
 */
void	ms_debug_print_args(const char *context, char **args)
{
	int	i;

	ft_printf(YELLOW "--- Debug: %s ---\n" RESET, context); 
	if (args == NULL)
	{
		ft_printf(YELLOW "  Args array is NULL.\n" RESET);
		ft_printf(YELLOW "--- End Debug ---\n" RESET);
		return;
	}
	if (args[0] == NULL)
	{
		ft_printf(YELLOW "  No command found (args[0] is NULL).\n" RESET);
		ft_printf(YELLOW "--- End Debug ---\n" RESET);
		return;
	}
	ft_printf(YELLOW "  Command: [%s]\n" RESET, args[0]);
		i = 1;
	while (args[i] != NULL)
	{
		ft_printf(YELLOW "  Opt/Arg %d: [%s]\n" RESET, i, args[i]);
		i++;
	}
	if (i == 1)
	{
		ft_printf(YELLOW "  (No options or arguments)\n" RESET);
	}
	ft_printf(YELLOW"--- End Debug ---\n" RESET);
}