/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:12:32 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/19 15:26:23 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*ms_new_ast_node(t_token_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*ms_create_and_link_redir(t_token **token_list, t_token *temp)
{
	t_ast	*redirect_node;
	
	redirect_node = ms_new_ast_node((*token_list)->type);
	*token_list = (*token_list)->next->next;
	redirect_node->left = ms_parse_redirection(token_list);
	redirect_node->right = ms_create_file_node(temp->next);
	free(temp->value);
	free(temp);
	return (redirect_node);
}
