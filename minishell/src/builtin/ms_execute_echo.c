/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:32:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/01 10:46:47 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_check_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	ms_handle_tilde_expansion(t_minishell *data, char *arg)
{
	char	*home_path;
	char	*expanded_path;

	if (arg[0] == '~' && (arg[1] == '/' || arg[1] == '\0'))
	{
		home_path = ms_getenv(data, "HOME");
		if (home_path)
		{
			if (arg[1] == '\0')
				ft_putstr_fd(home_path, STDOUT_FILENO);
			else
			{
				expanded_path = ft_strjoin(home_path, arg + 1);
				if (!expanded_path)
					return (ft_putstr_fd(arg, STDOUT_FILENO), (void)0);
				ft_putstr_fd(expanded_path, STDOUT_FILENO);
				free(expanded_path);
			}
		}
		else
			ft_putstr_fd(arg, STDOUT_FILENO);
	}
	else
		ft_putstr_fd(arg, STDOUT_FILENO);
}

static void	ms_print_echo_args(t_minishell *data, char **args, int i)
{
	while (args[i] != NULL)
	{
		ms_handle_tilde_expansion(data, args[i]);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

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
int	ms_execute_echo(t_minishell *data, char **args)
{
	int	i;
	int	print_newline;

	i = 1;
	print_newline = 1;
	if (args[1] == NULL)
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	while (args[i] && ms_check_n_flag(args[i]))
	{
		print_newline = 0;
		i++;
	}
	ms_print_echo_args(data, args, i);
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
