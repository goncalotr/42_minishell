/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:55:22 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/16 17:10:57 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ms_free_token(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return;
	free(token->value);
	if (token->args)
	{
		while (token->args[i])
		{
			free(token->args[i]);
			i++;
		}
		free(token->args);
	}
	free(token->expand_index);
	free(token);
}

void	ms_clean_token_list(t_token *token)
{
	t_token	*temp;
	
	while (token)
	{
		temp = token->next;
		ms_free_token(token);
		token = temp;
	}
}

void ms_clean_ast(t_ast *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	ms_clean_ast(node->left);
	ms_clean_ast(node->right);
	if (node->args)
	{
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);		
	}
	if (node->file_name)
		free(node->file_name);
	free(node);
}
