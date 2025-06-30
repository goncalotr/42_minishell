/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:31:09 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/30 14:55:42 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_join_nodes(t_token *dest, t_token *src)
{
	char	*new_value;

	new_value = ft_strjoin(dest->value, src->value);
	free(dest->value);
	dest->value = new_value;
	if (src->previous)
		src->previous->next = src->next;
	if (src->next)
		src->next->previous = src->previous;
	free(src->value);
	free(src);
}

t_token	*ms_join_cmd(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == TOKEN_CMD && temp->next
			&& temp->next->next && temp->next->next->next)
		{
			if (temp->next->next->next->type == TOKEN_CMD)
				ms_join_nodes(temp, temp->next->next->next);
		}
		temp = temp->next;
	}
	return (tokens);
}
