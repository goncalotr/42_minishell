/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:32:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 18:43:30 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Executes the echo builtin command using a simple argv array.
 *
 * Prints arguments to standard output. Handles the -n option
 * to suppress the trailing newline.
 *
 * @param args A NULL-terminated array of strings representing the command
 *             and its arguments (e.g., {"echo", "-n", "hello", NULL}).
 *             args[0] is expected to be "echo".
 * @return int Always returns 0 (success) for echo.
 * 
 * 1: Check for existance of args
 * 2: -n flag
 * 3: print the arguments (can be more than one with ' ' between them)
 * 
 * -n suppresses the trailing newline character.
 */
int	ms_execute_echo(char **args)
{
	int	i;
	int	print_newline;

	i = 1;
	print_newline = 1;
	if (args[1] == NULL)
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	if (ft_strncmp(args[1], "-n", 3) == 0)
	{
		print_newline = 0;
		i = 2;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
