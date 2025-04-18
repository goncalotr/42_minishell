/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:20:09 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 18:43:43 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Executes the env builtin command.
 *
 * Prints all environment variables passed via envp that contain an '='.
 * Currently ignores any arguments passed to the 'env' command itself.
 *
 * @param args The command arguments array (args[0] is "env"). Currently unused.
 * @param envp The environment variables array.
 * @return int Always returns 0 (success).
 */
int	ms_execute_env(char **args, char **envp)
{
	int	i;

	(void)args;
	i = 0;
	if (args[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	while (envp && envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '=') != NULL)
		{
			ft_putstr_fd(envp[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
