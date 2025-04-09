/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:05:03 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/09 02:20:31 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_exec(const char *path, char **args, char **envp)
{

}

static int parent_wait(pid_t pid)
{
	int	status;
	int	exit_status;
}

/**
 * @brief Executes an external command found in PATH.
 *        Handles fork, execve, and waiting for the child.
 * @param args The command arguments array (args[0] is the command).
 * @param envp The environment array.
 * @return The exit status of the executed command, or error codes
 *         (e.g., 127 for not found, 1 for fork/wait errors).
 * 
 * 1 Check args
 * 2 Find path and check if it exists
 * 3 fork
 * 4 if fork fails
 * 5 if child
 * 6 if parent
 */
int	ms_execute_external_command(char **args, char **envp)
{
	char	*path;
	pid_t	pid;

	if (!args || !args[0])
		return (0);

	path = ms_find_command_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
	}
	pid = fork();
	if (pid = -1)
	{
		perror("fork");
		free(path);
		return (1);
	}
	else if (pid == 0)
	{
		child_exec(path, args, envp);
	}
	else
	{
		free(path);
		return(parent_wait(pid));
	}
	return (1);
}
