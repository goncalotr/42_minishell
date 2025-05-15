/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:15:36 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/15 12:09:38 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_parsing(char *input)
{
	t_token		*list;

	list = NULL;
	list = ms_tokenization(input, list);
	list = ms_assign_state(list);
	list = ms_check_eof(list);
	list = ms_expansion_index(list);
	//list = expansao
	list = ms_quotes_off(list);
	ms_print_list(list);
}

t_token	*ms_assign_state(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (temp)
	{
		if (temp->value[0] == '\'')
			temp->state = SIMPLE_QUOTES;
		else if (temp->value[0] == '\"')
			temp->state = DOUBLE_QUOTES;
		temp = temp->next;	
	}
	return (list);
}

t_token *ms_check_eof(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (temp)
	{
		if (temp->type == TOKEN_HEREDOC && temp->next)
			temp->next->type = TOKEN_EOF;
		temp = temp->next;
	}
	return (list);
}
