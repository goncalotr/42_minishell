/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:16:48 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/20 10:16:56 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_free_token(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return ;
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

	if (!token)
		return ;
	while (token)
	{
		temp = token->next;
		free(token);
		token = temp;
	}
}

void	ms_clean_ast(t_ast *node)
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
		node->args = NULL;
	}
	if (node->file_name)
		free(node->file_name);
	free(node);
}
