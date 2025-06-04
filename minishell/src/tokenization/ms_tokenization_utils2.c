/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:56:27 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/02 17:00:36 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ms_is_file(t_token	*list)
{
	t_token	*last_node;
	
	last_node = ms_last_node(list);
	if (last_node == NULL)
		return (false);
	if(last_node->type == TOKEN_REDIR_IN || 
		last_node->type == TOKEN_REDIR_OUT || 
			last_node->type == TOKEN_APPEND)
		return (true);
	else
		return (false);
}

bool	ms_is_infile(t_token *list)
{
	t_token	*last_node;
	
	last_node = ms_last_node(list);
	if(last_node->type == TOKEN_REDIR_IN)
		return (true);
	else
		return (false);
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

char *ms_parse_quotes(char *input, int *i)
{
	int		quote_type;
	int		start;
	char	*word;
	
	word = NULL;
	while (input[*i] && !ms_isspace(input[*i]) && !ms_ismetachar(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			quote_type = input[*i];
			(*i)++;
			start = *i;
			while (input[*i] && input[*i] != quote_type)
			 	(*i)++;
			word = ms_str_append(word, ms_strndup(&input[start], *i - start));
			
			if (input[*i] == quote_type)
				(*i)++;
		}
		else
		{
			word = ms_append_char(word, input[*i]);
			(*i)++;
		}
	}
	return (word);
}

// t_token *ms_check_eof(t_token *list)
// {
// 	t_token	*temp;

// 	temp = list;
// 	while (temp)
// 	{
// 		if (temp->type == TOKEN_HEREDOC && temp->next)
// 			temp->next->type = TOKEN_EOF;
// 		temp = temp->next;
// 	}
// 	return (list);
// }


