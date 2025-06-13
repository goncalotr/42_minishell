/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:22 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/13 20:39:52 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ms_extract_cmd(char *input, int *i, t_token *list)
{
	char	*word;
	int 	k;

	
	word = malloc(ms_len_cmd(input, *i) + 1);
	if (!word)
		return NULL;
	k = 0;
	while (input[*i])
	{
		if(input[*i] == '|' ||  (input[*i] == '<' || input[*i] == '>'))
			break;
		word[k] = input[*i];
		(*i)++;
		k++;
	}
	word[k] = '\0';
	list = ms_append_node(list, word, TOKEN_CMD);
	free(word);
	return (list);
}

t_token	*ms_extract_file(char *input, int *i, t_token *list)
{
	char	*word;
	int 	k;

	
	word = malloc(ms_len_file(input, *i) + 1);
	if (!word)
		return NULL;
	k = 0;
	while (input[*i])
	{
		if(input[*i] == 32 || (input[*i] >= 7 && input[*i] <= 13))
			break;
		if(input[*i] == '|' ||  (input[*i] == '<' || input[*i] == '>'))
			break;
		word[k] = input[*i];
		(*i)++;
		k++;
	}
	word[k] = '\0';
	if (ms_is_infile(list))
		list = ms_append_node(list, word, TOKEN_INFILE);
	else
		list = ms_append_node(list, word, TOKEN_OUTFILE);		
	free(word);
	return (list);
}

t_token	*ms_extract_quotes(char *input, int *i, t_token *list)
{
	char	*word;

	word = ms_parse_quotes(input, i);
	if (!word)
		return list;
	if (ms_is_file(list))
	{
		if (ms_is_infile(list))
			list = ms_append_node(list, word, TOKEN_INFILE);
		else
			list = ms_append_node(list, word, TOKEN_OUTFILE);
	}
	else
		list = ms_append_node(list, word, TOKEN_CMD);
	free(word);
	return (list);
}

t_token *ms_start_tokenization(char *input, t_token *list)
{
	int			i;
	
	i = 0;
	input = ms_remove_whitespaces(input);
	while (input[i])
	{
		if((input[i] == '|') || (input[i] == '<' || input[i] == '>'))
			list = ms_extract_operator(input, &i, list);
		else if((input[i] == '\'') || (input[i] == '\"'))
			list = ms_extract_quotes(input, &i, list);
		else if(ms_is_file(list))
			list =  ms_extract_file(input, &i, list);
		else
			list = ms_extract_cmd(input, &i, list);
	}
	return (list);
}

t_token	*ms_tokenization(char *input)
{
	t_token		*tokens;

	tokens = NULL;
	tokens = ms_start_tokenization(input, tokens);
	tokens = ms_assign_state(tokens);
	tokens = ms_expansion_index(tokens);
	// tokens = ms_expansion(tokens);
	// tokens = ms_quotes_off(tokens);
	return (tokens);
}
