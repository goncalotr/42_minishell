/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:10:39 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/26 13:30:42 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

/**
 * function for exit built-in
 * 
 * exit - ms_cleanup_shell
 * ctrl d - ms_cleanup_shell(data)
 */
void	ms_exit_shell(t_minishell *data, int exit_code)
{
	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
	}
	ms_clean_all(data);
	clear_history();
	exit(exit_code);
}

/*
** @brief Handles the case for `exit` with one argument (the exit code).
*/
static void	ms_handle_exit_with_one_arg(t_minishell *data, char *arg)
{
	long long	exit_code_ll;

	if (ft_atol_validate(arg, &exit_code_ll))
		ms_exit_shell(data, (unsigned char)exit_code_ll);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		ms_exit_shell(data, 255);
	}
}

/**
 * @brief Executes the exit builtin command.
 *
 * Terminates the shell process with a specified status or the status
 * of the last command. Handles errors for non-numeric or too many args.
 *
 * @param args The command arguments array (args[0] is "exit").
 * @param last_exit_status The exit status of the previously executed command.
 * @return int Returns 1 if there are too many arguments (and doesn't exit),
 *             otherwise, it calls exit() and does not return.
 * 	
 * 1 Count arguments
 * 2 Print exit
 * 3 If only one argument
 * 4 2 aarguments, either valid or non numeric
 * 5 Too many arguments
 */
int	ms_execute_exit(char **args, t_minishell *data)
{
	int			argc;

	argc = 0;
	while (args[argc] != NULL)
		argc++;
	if (argc == 1)
		ms_exit_shell(data, data->last_exit_status);
	else if (argc == 2)
		ms_handle_exit_with_one_arg(data, args[1]);
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
