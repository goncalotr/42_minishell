/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tree_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:27:10 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/18 17:29:46 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ms_prepare_heredocs(t_ast *node)
{
	char	*node_nbr;

	if (!node)
		return ;
	if (node->type == TOKEN_HEREDOC)
	{
		if (node->file_name)
			return ;
		node_nbr = ft_itoa(node->node_nbr);
		if (!node_nbr)
			return ;
		node->file_name = ft_strjoin("/tmp/heredoc_", node_nbr);
		free(node_nbr);
		if (!node->file_name)
			return ;
		ms_exec_heredoc(node);
	}
	ms_prepare_heredocs(node->left);
	ms_prepare_heredocs(node->right);
}

void	ms_clean_heredocs(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == TOKEN_HEREDOC)
	{
		if (unlink(node->file_name) == -1)
			perror ("unlink");
		free(node->file_name);
		node->file_name = NULL;
	}
	ms_clean_heredocs(node->left);
	ms_clean_heredocs(node->right);
}

void	ms_command_not_found(char **cmds)
{
	if (!cmds || !cmds[0])
	{
		ft_putstr_fd("command not found: \n", 2);
		return ;
	}
	ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}
