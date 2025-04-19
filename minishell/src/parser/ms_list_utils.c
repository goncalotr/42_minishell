/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:28:17 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/04/19 19:57:44 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_tokens *ms_last_node(t_tokens *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		 list = list->next;
	return (list);
}
t_tokens *ms_append_node(t_tokens *list, char  *input, t_type type)
{
	t_tokens	*last_node;
	t_tokens	*new_node;
	
	new_node = malloc(sizeof(t_tokens));
	if (!new_node)
		return (NULL);
	new_node->token = ft_strdup(input);
	new_node->type = type;
	new_node->next = NULL;
	if  (list == NULL)
		list = new_node;
	else
	{
		last_node = ms_last_node(list);
		last_node->next = new_node;
	}
	return (list);
}

void ms_print_list(t_tokens *list)
{
	char	*type[] = {"WORD", "PIPE", "IN", "OUT", "HEREDOC", "APPEND"};

	while (list)
	{
		ft_printf("---------------------------------\n");
		ft_printf("Token -> %s\n", list->token);
		ft_printf("Type -> %s\n", type[list->type]);
		list = list->next;
	}
}
