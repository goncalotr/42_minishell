/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:59 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/27 17:00:36 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

	cwd_buffer = getcwd(NULL, 0);
	if (cwd_buffer != NULL)
	{
		// Success! Print the real path and we are done.
		ft_putstr_fd(cwd_buffer, 1);
		ft_putstr_fd("\n", 1);
		free(cwd_buffer);
		return (0);
	}
	if (errno == ENOENT)
	{
		// Fallback to our internal PWD variable.
		char *pwd_from_env = ms_getenv(data, "PWD");
		if (pwd_from_env)
		{
			ft_putstr_fd(pwd_from_env, 1);
			ft_putstr_fd("\n", 1);
			// We don't print a system error because this is our graceful fallback.
			return (0); // Success, we printed something.
		}
	}
	perror("minishell: pwd");
	return (1);
}
