/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:59 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/18 19:44:07 by goteixei         ###   ########.fr       */
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
int	ms_execute_pwd(char **args)
{
	char	*cwd_buffer;

	if (args[1] != NULL)
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return (1);
	}
	cwd_buffer = getcwd(NULL, 0);
	if (cwd_buffer == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putstr_fd(cwd_buffer, 1);
	ft_putstr_fd("\n", 1);
	free(cwd_buffer);
	return (0);
}
