/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:14 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 16:49:31 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	ms_child_process_exec(t_ast *node, t_minishell *data)
{
	int		i;
	char	full_path[PATH_MAX];

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_strchr(node->args[0], '/'))
		ms_handle_absolute_path(node->args, data->envp);
	i = 0;
	while (data->paths && data->paths[i])
	{
		ft_strlcpy(full_path, data->paths[i], sizeof(full_path));
		ft_strlcat(full_path, "/", sizeof(full_path));
		ft_strlcat(full_path, node->args[0], sizeof(full_path));
		if (access(full_path, X_OK) == 0)
			execve(full_path, node->args, data->envp);
		i++;
	}
	ms_command_not_found(node->args);
	ms_clean_all(data);
	exit(127);
}

int	ms_parent_process_wait(pid_t pid)
{
	int	status;
	int	final_exit_status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		final_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		final_exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
	else
		final_exit_status = 1;
	return (final_exit_status);
}

int	ms_exec_external_command(t_ast *node, t_minishell *data)
{
	pid_t	pid;
	int		exit_status;

	ms_signal_handlers_set_non_interactive();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		ms_child_process_exec(node, data);
	exit_status = ms_parent_process_wait(pid);
	ms_signal_handlers_set_interactive();
	return (exit_status);
}

int	ms_exec_cmd(t_ast *node, t_minishell *data)
{
	int	builtin_status;

	if (node->args == NULL || node->args[0] == NULL)
		return (0);
	builtin_status = ms_exec_cmd_builtins(data, node);
	if (builtin_status != -1)
		return (builtin_status);
	return (ms_exec_external_command(node, data));
}
