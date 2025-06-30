/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:15:36 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/30 14:52:26 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*ms_parse_command(t_token **token)
{
	t_ast	*command_node;

	if (!(*token))
		return (NULL);
	command_node = ms_new_ast_node(TOKEN_CMD);
	command_node->args = ms_cpy_array((*token)->args);
	ms_free_array((*token)->args);
	free((*token));
	return (command_node);
}

t_ast	*ms_create_file_node(t_token *token)
{
	t_ast	*file_node;

	file_node = ms_new_ast_node(token->type);
	if (!file_node)
		return (NULL);
	file_node->type = token->type;
	file_node->args = malloc(sizeof(char *) * 2);
	if (!file_node->args)
	{
		free(file_node);
		return (NULL);
	}
	file_node->args[0] = ft_strdup(token->value);
	file_node->args[1] = NULL;
	free(token->value);
	free(token);
	return (file_node);
}

t_ast	*ms_parse_redirection(t_token	**token_list)
{
	t_ast	*redirect_node;
	t_token	*start;

	if (!(*token_list))
		return (NULL);
	start = *token_list;
	if ((*token_list)->type >= TOKEN_REDIR_IN
		&& (*token_list)->type <= TOKEN_HEREDOC)
		return (ms_create_and_link_redir(token_list));
	while ((*token_list) && (*token_list)->next)
	{
		if ((*token_list)->next->type >= TOKEN_REDIR_IN
			&& (*token_list)->next->type <= TOKEN_HEREDOC)
		{
			(*token_list)->next = (*token_list)->next->next->next;
			redirect_node = ms_new_ast_node((*token_list)->next->type);
			redirect_node->left = ms_parse_redirection(&start);
			redirect_node->right = ms_create_file_node(
					(*token_list)->next->next);
			ms_free_token((*token_list)->next);
			return (redirect_node);
		}
		*token_list = (*token_list)->next;
	}
	return (ms_parse_command(&start));
}

t_ast	*ms_parse_pipes(t_token **token_list)
{
	t_token	*start;
	t_token	*pipe_token;
	t_ast	*pipe_node;

	start = (*token_list);
	while (*token_list && (*token_list)->next)
	{
		if ((*token_list)->next->type == TOKEN_PIPE)
		{
			pipe_token = (*token_list)->next;
			(*token_list)->next = NULL;
			pipe_node = ms_new_ast_node(TOKEN_PIPE);
			pipe_node->left = ms_parse_redirection(&start);
			pipe_node->right = ms_parse_pipes(&(pipe_token->next));
			free(pipe_token->value);
			free(pipe_token);
			return (pipe_node);
		}
		*token_list = (*token_list)->next;
	}
	return (ms_parse_redirection(&start));
}

t_ast	*ms_parse_tokens(t_token	**token_list)
{
	if (!token_list)
		return (NULL);
	return (ms_parse_pipes(token_list));
}
