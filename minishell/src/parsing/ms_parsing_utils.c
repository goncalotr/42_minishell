/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:12:32 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/05 12:37:16 by jpedro-f         ###   ########.fr       */
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
	return (node);
}

t_ast *ms_create_and_link_redir(t_token **token_list, t_token *temp)
{
	t_ast *redirect_node = ms_new_ast_node(temp->type);

	t_token *file_token = temp->next;
	if (!file_token)
	{
		free(temp->value);
		free(temp);
		free(redirect_node);
		return (NULL);
	}
	*token_list = file_token->next;
	redirect_node->right = ms_create_file_node(file_token);
	if (*token_list)
	{
		if ((*token_list)->type >= TOKEN_REDIR_IN && (*token_list)->type <= TOKEN_HEREDOC)
			redirect_node->left = ms_parse_redirection(token_list);
		else
			redirect_node->left = ms_parse_command(token_list);
	}
	else
		redirect_node->left = NULL;
	free(temp->value);
	free(temp);
	return redirect_node;
}
