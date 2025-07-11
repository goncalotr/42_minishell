/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:59 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 18:37:37 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ms_execute_pwd_aux(char **args)
{
	if (args[1] != NULL)
	{
		if (args[1][0] == '-')
		{
			ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": invalid option\n", STDERR_FILENO);
			return (2);
		}
	}
	return (0);
}

/**
 * @brief Executes the 'pwd' built-in command.
 * Gets the current path using getcwd and prints it.
 * @param args Argument vector. Checks if too many args are provided.
 * @return 0 on success, 1 on failure.
 * 
 * Part 1: Check args
 * Part 2: Get current working directory
 * Part 3: Print the path to the std output
 * Part 4: Free buffer
 * Part 5: Return value
 */
int	ms_execute_pwd(char **args, t_minishell *data)
{
	char	*cwd_buffer;
	char	*pwd_from_env;

	if (ms_execute_pwd_aux(args) != 0)
		return (2);
	cwd_buffer = getcwd(NULL, 0);
	if (cwd_buffer != NULL)
	{
		ft_putstr_fd(cwd_buffer, 1);
		ft_putstr_fd("\n", 1);
		free(cwd_buffer);
		return (0);
	}
	if (errno == ENOENT)
	{
		pwd_from_env = ms_getenv(data, "PWD");
		if (pwd_from_env)
		{
			ft_putstr_fd(pwd_from_env, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
	}
	perror("minishell: pwd");
	return (1);
}
