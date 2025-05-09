/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:15:36 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/09 16:01:04 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_parsing(char *input)
{
	t_token		*list;

	list = NULL;
	list = ms_tokenization(input, list);
	list = ms_check_eof(list);
	// list = ms_remove_quotes(list);
	ms_print_list(list);
}

// t_token *ms_remove_quotes(t_token *list)
// {
// 	t_token	*temp;

// 	temp = list;
// 	while (temp)
// 	{
// 		temp = temp->next;
// 	}
	
// }

t_token *ms_check_eof(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (temp)
	{
		if (temp->type == TOKEN_HEREDOC)
			temp->next->type = TOKEN_EOF;
		temp = temp->next;
	}
	return (list);
}

bool ms_check_expansion(char *input, t_token_type type)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && type != 9)
			return (true);
		i++;
	}
	return (false);
}