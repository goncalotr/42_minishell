/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:15:36 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/19 15:41:03 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*ms_parse_command(t_token **token)
{
	t_ast	*command_node;
	char	**args;

	args = ft_split((*token)->value, ' ');
	if (!args)
		return NULL;
	command_node = ms_new_ast_node(TOKEN_CMD);
	command_node->args = args;
	free(*token);
	return(command_node);
}

t_ast	*ms_create_file_node(t_token *token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = token->value;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	free(token);
	return (node);
}

t_ast	*ms_parse_redirection(t_token	**token_list)
{
	t_token	*temp;
	t_token	*next_token;
	t_ast	*redirect_node;

	if (!*token_list) 
		return (NULL);
	temp = *token_list;
	if ((*token_list)->type >= TOKEN_REDIR_IN
		&& (*token_list)->type <= TOKEN_HEREDOC)
			return (ms_create_and_link_redir(token_list, temp));
	while (*token_list && (*token_list)->next)
	{
		next_token = (*token_list)->next;
		if (next_token->type >= TOKEN_REDIR_IN
			&& next_token->type <= TOKEN_HEREDOC)
			{
				redirect_node = ms_new_ast_node(next_token->type);
				(*token_list)->next = next_token->next->next;
				redirect_node->left = ms_parse_redirection(&temp);
				redirect_node->right = ms_create_file_node(next_token->next);
				return (free(next_token->value), free(next_token), redirect_node);
			}
		*token_list = next_token;
	}
	return (ms_parse_command(&temp));
}

t_ast	*ms_parse_pipes(t_token **token_list)
{
	t_token	*temp;
	t_token	*next_token;
	t_ast	*pipe_node;

	temp = *token_list;
	while (*token_list && (*token_list)->next)
	{
		next_token = (*token_list)->next;
		if (next_token->type == TOKEN_PIPE)
		{
			pipe_node = ms_new_ast_node(next_token->type);
			(*token_list)->next = NULL;
			pipe_node->left = ms_parse_redirection(&temp);
			pipe_node->right = ms_parse_pipes(&(next_token->next));
			free(next_token->value);
			free(next_token);
			return (pipe_node);
			}
		*token_list = next_token;
	}
	return (ms_parse_redirection(&temp));
}

t_ast 	*ms_parse_tokens(t_token	**token_list)
{ 
	if (!token_list)
		return (NULL);
	return (ms_parse_pipes(token_list));
}
