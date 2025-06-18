/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:05 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/17 17:56:28 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ms_extract_word(char *input, int *i, t_token *list)
{
	char	*word;

	if (ms_is_file(list))
	{
		word = ms_cpy_token(input, i);
		if (!word)
			return list;
		if (ms_is_infile(list))
			list = ms_append_node(list, word, TOKEN_INFILE);
		else
			list = ms_append_node(list, word, TOKEN_OUTFILE);
	}
	else
	{
		word = ms_cpy_token_cmd(input, i);
		if (!word)
			return list;
		list = ms_append_node(list, word, TOKEN_CMD);	
	}
	free(word);
	return (list);
}

t_token	*ms_extract_eof(t_token *list, char * input, int *i)
{
	char *eof;
	
	eof = ms_cpy_token(input, i);
	list = ms_append_node(list, eof, TOKEN_EOF);
	free(eof);
	return (list);
}

t_token *ms_extract_operator(char *input, int *i, t_token *list)
{
	if (input[*i] == '|')
		list = ms_append_node(list, "|", TOKEN_PIPE);
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		list = ms_append_node(list, "<<", TOKEN_HEREDOC);
		*i += 2;
		list = ms_extract_eof(list, input, i);
		return (list);
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		list = ms_append_node(list, ">>", TOKEN_APPEND);
		*i += 2;
		return (list);
	}
	else if (input[*i] == '<')
		list = ms_append_node(list, "<", TOKEN_REDIR_IN);
	else if (input[*i] == '>')
		list = ms_append_node(list, ">", TOKEN_REDIR_OUT);
	(*i)++;
	return (list);
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