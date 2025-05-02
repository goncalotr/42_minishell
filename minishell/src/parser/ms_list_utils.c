/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:28:17 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/04/19 21:10:20 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Returns the last node in a linked list of tokens.
 *
 * This function iterates through the `t_tokens` linked list until it reaches
 * the final node (i.e., the node where `next` is NULL). If the list is empty,
 * it returns NULL.
 * 
 * @param list The head of the token list.
 * 
 * @return A pointer to the last node in the list, or NULL if the list is empty.
 */
t_tokens *ms_last_node(t_tokens *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		 list = list->next;
	return (list);
}
/**
 * @brief Creates a new token node and appends it to the end of the token list.
 *
 * This function allocates memory for a new `t_tokens` node, duplicates the given
 * input string as the token's content, assigns its type, and appends it to the
 * end of the existing linked list. If the list is initially NULL, it creates and
 * returns a new list with a single node.
 * 
 * @param list The current token list to append to (can be NULL to start a new list).
 * @param input The string value of the token (e.g. command, operator).
 * @param type The type of the token (e.g. WORD, PIPE, IN, OUT).
 * 
 * @return The updated token list including the newly added node.
 */
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
