/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:16:48 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 14:47:31 by jpedro-fvm       ###   ########.fr       */
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

// Helper to free a single token and its contents
static void	ms_free_one_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	if (token->args)
		ms_free_array(token->args);
	free(token->expand_index);
	free(token);
}

// Main function to free the whole list
void	ms_clean_token_list(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	while (token)
	{
		temp = token->next;
		ms_free_one_token(token);
		token = temp;
	}
}

void	ms_free_token(t_token *token)
{
	if (!token)
		return (token);
	free(token->value);
	free(token);
}
