/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:12:32 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/16 16:54:14 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*ms_new_ast_node(t_token_type type)
{
	t_ast		*node;
	static int	node_nbr = 0;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->node_nbr = node_nbr++;
	node->file_name = NULL;
	return (node);
}

t_ast *ms_create_and_link_redir(t_token **token_list)
{
	t_ast *redirect_node;
	t_token *file_token;
	t_token	*redir_token;
	
	redir_token = (*token_list);
	file_token = redir_token->next;
	(*token_list) = file_token->next;
	redirect_node = ms_new_ast_node(redir_token->type);
	redirect_node->right = ms_create_file_node(file_token);
	redirect_node->left = ms_parse_redirection(token_list);
	free(redir_token->value);
	free(redir_token);
	return redirect_node;
}
