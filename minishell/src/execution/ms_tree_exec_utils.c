/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tree_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:27:10 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/05 15:15:18 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ms_prepare_heredocs(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == TOKEN_HEREDOC)
		ms_exec_heredoc(node);
	ms_prepare_heredocs(node->left);
	ms_prepare_heredocs(node->right);
}