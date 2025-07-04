/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:05:03 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/18 10:56:57 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// This function runs in the child process.
// It attempts to execute the command. If execve fails, it prints an error
// and exits the child process with an appropriate status code.

//eacces
//enoent
//126 permission denied
//127 command not found
static void	ms_child_exec(const char *path, char **args, char **envp)
{
	execve(path, args, envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(EXIT_FAILURE);
}

// This function runs in the parent process.
// It waits for the child process (pid) to finish and returns its exit status.
/**
 * 	Check how the child terminated
	if (WIFEXITED(status))
	{
		Child exited normally, return its exit code
		exit_status = WEXITSTATUS(status);
	}
 */
static int	ms_parent_wait(pid_t pid)
{
	int	status;
	int	exit_status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid");
		return (1);
	}
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		exit_status = 128 + WTERMSIG(status);
	}
	else
	{
		exit_status = 1;
	}
	return (exit_status);
}

static int	ms_execute_error(char **args, int mode)
{
	if (mode == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (126);
	}
	else if (mode == 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (127);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
	}
}

static void	ms_child_exec_help(char **args, char **envp, char *path)
{
	ms_child_exec(path, args, envp);
	free(path);
	exit(EXIT_FAILURE);
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
int	ms_execute_external_command(char **envp, char **args)
{
	char	*path;
	pid_t	pid;

	if (!args || !args[0])
		return (0);
	path = ms_find_command_path(args[0], envp);
	if (!path)
	{
		if (ft_strchr(args[0], '/') && errno == EACCES)
			return (ms_execute_error(args, 1));
		else if (ft_strchr(args[0], '/') && errno == ENOENT)
			return (ms_execute_error(args, 2));
		else
			return (ms_execute_error(args, 3));
	}
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), free(path), 1);
	else if (pid == 0)
		ms_child_exec_help(args, envp, path);
	else
		return (free(path), ms_parent_wait(pid));
	return (1);
}
