/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:55:39 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 13:57:40 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	ms_exec_cmd_builtins(t_minishell *data, t_ast *node)
{
	if (!node->args || !node->args[0])
		return (0);
	if (ft_strcmp(node->args[0], "cd") == 0)
		return (ms_execute_cd(data, node->args));
	if (ft_strcmp(node->args[0], "echo") == 0)
		return (ms_execute_echo(data, node->args));
	if (ft_strcmp(node->args[0], "env") == 0)
		return (ms_execute_env(data, node->args));
	if (ft_strcmp(node->args[0], "exit") == 0)
		return (ms_execute_exit(node->args, data));
	if (ft_strcmp(node->args[0], "export") == 0)
		return (ms_execute_export(node->args, data));
	if (ft_strcmp(node->args[0], "pwd") == 0)
		return (ms_execute_pwd(node->args, data));
	if (ft_strcmp(node->args[0], "unset") == 0)
		return (ms_execute_unset((node->args), data));
	return (-1);
}

void	ms_handle_absolute_path(char **args, char **envp)
{
	struct stat	file_stat;

	if (access(args[0], F_OK) == -1)
	{
		perror(args[0]);
		exit(127);
	}
	stat(args[0], &file_stat);
	if (S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (access(args[0], X_OK) == -1)
	{
		perror(args[0]);
		exit(126);
	}
	execve(args[0], args, envp);
	perror(args[0]);
	exit(126);
}
