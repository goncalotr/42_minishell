/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:28:17 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/30 13:41:55 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ms_last_node(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_token	*ms_append_node(t_token *list, char *input, t_token_type type)
{
	t_token	*last_node;
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(input);
	new_node->type = type;
	new_node->args = NULL;
	new_node->expand = NULL;
	new_node->state = GENERAL;
	new_node->expand_index = NULL;
	new_node->previous = NULL;
	new_node->next = NULL;
	if (list == NULL)
		list = new_node;
	else
	{
		last_node = ms_last_node(list);
		last_node->next = new_node;
		new_node->previous = last_node;
	}
	return (list);
}
