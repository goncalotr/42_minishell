/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:15:36 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/10 12:49:29 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"


t_ast	*ms_parse_command(t_token **token)
{
	t_ast	*command_node;
	char	**args;

	if (!(*token))
		return NULL;
	args = ft_split((*token)->value, ' ');
	if (!args)
		return NULL;
	command_node = ms_new_ast_node(TOKEN_CMD);
	command_node->args = args;
	free(*token);
	return(command_node);
}


/*
t_ast	*ms_parse_command(t_token **token_list_ptr)
{
	t_ast	*command_node;
	char	*full_str;
	char	*temp_str;
	t_token	*current;
	t_token	*to_free;

	// Check for an empty list
	if (!token_list_ptr || !*token_list_ptr)
		return (NULL);
	current = *token_list_ptr;
	// 1. Start with the value of the first token.
	full_str = ft_strdup(current->value);
	if (!full_str)
		return (NULL); // Malloc failed
	// 2. Consume the first token
	to_free = current;
	current = current->next;
	free(to_free->value);
	free(to_free);
	// 3. Loop through subsequent tokens and append them if they are also part of the command
	while (current && current->type == TOKEN_CMD)
	{
		// Append a space
		temp_str = ft_strjoin(full_str, " ");
		free(full_str);
		full_str = temp_str;
		if (!full_str)
			return (NULL); // Malloc failed
		// Append the next token's value
		temp_str = ft_strjoin(full_str, current->value);
		free(full_str);
		full_str = temp_str;
		if (!full_str)
			return (NULL); // Malloc failed
		// Consume the token we just appended
		to_free = current;
		current = current->next;
		free(to_free->value);
		free(to_free);
	}
	// 4. Update the original list to point to the remaining unconsumed tokens
	*token_list_ptr = current;
	// 5. Create the AST node by splitting the combined string
	command_node = ms_new_ast_node(TOKEN_CMD);
	if (!command_node)
	{
		free(full_str);
		return (NULL);
	}
	command_node->args = ft_split(full_str, ' ');
	free(full_str);
	if (!command_node->args)
	{
		free(command_node);
		return (NULL);
	}
	return (command_node);
}
*/

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
	file_node->args[0] = token->value;
	file_node->args[1] = NULL;
	free(token);
	return (file_node);
}

t_ast	*ms_parse_redirection(t_token	**token_list)
{
	t_ast	*redirect_node;
	t_token *start;
	t_token	*file_token;
	t_token	*redir_token;
	
	if (!(*token_list))
		return NULL;
	start = *token_list;
	if ((*token_list)->type >= TOKEN_REDIR_IN 
		&& (*token_list)->type<= TOKEN_HEREDOC)
		return (ms_create_and_link_redir(token_list));
	while ((*token_list) && (*token_list)->next)
	{
		if ((*token_list)->next->type >= TOKEN_REDIR_IN 
				&& (*token_list)->next->type<= TOKEN_HEREDOC)
			{
				redir_token = (*token_list)->next;
				file_token = redir_token->next;
				(*token_list)->next = file_token->next;
				redirect_node = ms_new_ast_node(redir_token->type);
				redirect_node->left = ms_parse_redirection(&start);
				redirect_node->right = ms_create_file_node(file_token);
				return (redirect_node);
			}
		*token_list = (*token_list)->next;
	}
	return (ms_parse_command(&start));
}

t_ast	*ms_parse_pipes(t_token **token_list)
{
	t_token *start;
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

t_ast 	*ms_parse_tokens(t_token	**token_list)
{ 
	if (!token_list)
		return (NULL);
	return (ms_parse_pipes(token_list));
}
