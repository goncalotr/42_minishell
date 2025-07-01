/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:01 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 13:54:09 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	ms_exec_redir_out(t_ast *node, t_minishell *data)
{
	int		fd;
	int		status;
	int		flags;

	if (node->type == TOKEN_REDIR_OUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(node->right->args[0], flags, 0644);
	if (fd < 0)
	{
		perror("open outfile");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	status = ms_exec_tree(node->left, data);
	dup2(data->stdout_fd, STDOUT_FILENO);
	return (status);
}

int	ms_exec_redir_in(t_ast *node, t_minishell *data)
{
	int		fd;
	int		status;

	if (node->type == TOKEN_HEREDOC)
		fd = open(node->file_name, O_RDONLY);
	else
		fd = open(node->right->args[0], O_RDONLY);
	if (fd < 0)
	{
		perror("open infile");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	status = ms_exec_tree(node->left, data);
	dup2(data->stdin_fd, STDIN_FILENO);
	return (status);
}
