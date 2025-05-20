/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tree_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:43:03 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/20 15:54:59 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ms_exc_cmd(t_ast *node, t_minishell *data)
{
	int		i;
	char 	full_path[1024];
	pid_t	pid;
	int		status;
	
	i = 0;
	if ((pid = fork()) == 0)
	{
		if (ft_strchr(node->args[0], '/'))
		{
			if (access(node->args[0], X_OK) == 0)
				execve(node->args[0], node->args, data->envp);
			perror(node->args[0]);
			exit(127);
		}
		while (data->paths[i])
		{
			ft_strlcpy(full_path, data->paths[i], sizeof(full_path));
			ft_strlcat(full_path, "/", sizeof(full_path));
			ft_strlcat(full_path, node->args[0], sizeof(full_path));
			if (access(full_path, X_OK) == 0)
				execve(full_path, node->args, data->envp);
			i++;
		}
		perror(node->args[0]);
		exit (127);
	}
	waitpid(pid, &status, 0);
	return WEXITSTATUS(status);
}

int	ms_exec_tree(t_ast *node, t_minishell *data)
{
	if (!node)
		return 0;
	if (node->type == TOKEN_CMD)
		return (ms_exec_cmd(node, data));
	if (node->type == TOKEN_PIPE)
		return (ms_exec_pipe(node));
	if (node->type == TOKEN_REDIR_IN)
		return (ms_exec_redir_in(node));
	if (node->type == TOKEN_REDIR_OUT)
		return (ms_exec_redir_out(node));
	if (node->type == TOKEN_APPEND)
		return (ms_exec_append(node));
		if (node->type == TOKEN_HEREDOC)
		return (ms_exec_heredoc(node));
	if (node->type == TOKEN_INFILE || node->type == TOKEN_OUTFILE
		|| node->type == TOKEN_EOF)
		return (0);
	return (1);
}