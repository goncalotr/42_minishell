/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tree_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:27:10 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/06 18:28:54 by jpedro-f         ###   ########.fr       */
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
		node->file_name = ft_strjoin("heredoc_", node_nbr);
		free(node_nbr);
		if (!node->file_name)
			return ; 
		ms_exec_heredoc(node);
	}
	ms_prepare_heredocs(node->left);
	ms_prepare_heredocs(node->right);
}

void	ms_strip_extra_redirs_in(t_ast *node)
{
	t_ast 	*prev;
	t_ast	*temp;

	prev = NULL;
	temp = node;
	while (temp && temp->left && (temp->left->type == TOKEN_HEREDOC
			|| temp->left->type == TOKEN_REDIR_IN))
	{
		prev = temp;
		temp = temp->left;
	}
	if (prev)
		prev->left = NULL;
}
