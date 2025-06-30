/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tree_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:43:03 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/30 15:51:35 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	ms_exec_tree(t_ast *node, t_minishell *data)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_CMD)
		return (ms_exec_cmd(node, data));
	if (node->type == TOKEN_PIPE)
		return (ms_exec_pipe(node, data));
	if (node->type == TOKEN_REDIR_IN)
		return (ms_exec_redir_in(node, data));
	if (node->type == TOKEN_REDIR_OUT)
		return (ms_exec_redir_out(node, data));
	if (node->type == TOKEN_APPEND)
		return (ms_exec_redir_out(node, data));
	if (node->type == TOKEN_HEREDOC)
		return (ms_exec_redir_in(node, data));
	if (node->type == TOKEN_INFILE || node->type == TOKEN_OUTFILE
		|| node->type == TOKEN_EOF)
		return (0);
	return (1);
}
