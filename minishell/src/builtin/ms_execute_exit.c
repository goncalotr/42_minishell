/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:10:39 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/08 23:43:41 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int g_last_exit_status;

//todo implement in libft
static bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}

/**
 * @brief Attempts to convert a string to a long long, checking for validity.
 *        Checks for overflow and ensures the entire string represents a number
 *        (allowing optional leading '+' or '-').
 * @param str The string to convert.
 * @param n_out Pointer where the resulting long long will be stored if valid.
 * @return true if the string is a valid representation of a long long,
 *         false otherwise (overflow, non-digit characters).
 * 
 * ft_isdigit -> must have at least one digit
 * second ft_isspace -> check for trailing spaces
 * before multiplying or adding we check that the result * 10 won't overflow
 */
bool	ft_atol_validate(const char *str, long long *n_out)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;

	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
	{
		if (sign == 1 && (result > LLONG_MAX / 10 || \
		   (result == LLONG_MAX / 10 && (str[i] - '0') > LLONG_MAX % 10)))
			return (false);
		if (sign == -1 && (result > LLONG_MAX / 10 || \
		   (result == LLONG_MAX / 10 && (str[i] - '0') > LLONG_MAX % 10 + 1)))
			return (false);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (false);
	*n_out = sign * result;
	return (true);
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
int	ms_execute_exit(char **args)
{
	int	argc;
	long long	exit_code_ll;

	argc = 0;
	while (args[argc] != NULL)
		argc++;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	
	if (argc == 1)
	{
		exit(g_last_exit_status);
	}
	else if (argc == 2)
	{
		if (ft_atol_validate(args[1], &exit_code_ll))
		{
			exit((unsigned char)exit_code_ll);
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(255);
		}
	}
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
