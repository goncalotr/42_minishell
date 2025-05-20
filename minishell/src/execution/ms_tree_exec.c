/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tree_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:43:03 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/20 12:53:08 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ms_exec_tree(t_ast *node)
{
	if (!node)
		return 0;
	if (node->type == TOKEN_CMD)
		return (ms_exec_cmd(node));
	if (node->type == TOKEN_PIPE)
		return (ms_exec_pipe(node));
	if (node->type == TOKEN_REDIR_IN)
		return (ms_exec_redir_in(node));
	if (node->type == TOKEN_REDIR_OUT)
		return (ms_exec_redir_out(node));
	if (node->type == TOKEN_APPEND)
		return (ms_exec_append(node));
	if (node->type == TOKEN_APPEND)
		return (ms_exec_append(node));
	if (node->type == TOKEN_INFILE || node->type == TOKEN_OUTFILE
		|| node->type == TOKEN_EOF)
		return (0);
	return (1);
}