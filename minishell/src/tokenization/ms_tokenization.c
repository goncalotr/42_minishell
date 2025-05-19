/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:22 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/19 15:06:33 by jpedro-f         ###   ########.fr       */
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
		else if ((input[*i] == '\'') || (input[*i] == '\"'))
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

t_token *ms_extract_quotes(char *input, int *i, t_token *list)
{
	char	quote_type;
	char	*quote;
	int		k;
	int		len;
	
	quote_type = input[*i];
	len = ms_quote_len(input, *i);
	quote = malloc(len + 2);
	if (!quote)
		return NULL;
	k = 0;
	while (input[*i] && k <= len)
		quote[k++] = input[(*i)++];
	quote[k] = '\0';
	if(ms_is_file(list))
	{
		if (ms_is_infile(list))
			list = ms_append_node(list, quote, TOKEN_INFILE);
		else
			list = ms_append_node(list, quote, TOKEN_OUTFILE);
	}
	else
		list = ms_append_node(list, quote, TOKEN_CMD);
	free(quote);
	return (list);	
}

t_token *ms_start_tokenization(char *input, t_token *list)
{
	int			i;
	
	i = 0;
	input = ms_remove_whitespaces(input);
	while (input[i])
	{
		ms_skip_whitespaces(&i, input);
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
	t_token		*list;

	list = NULL;
	list = ms_start_tokenization(input, list);
	list = ms_assign_state(list);
	list = ms_check_eof(list);
	list = ms_expansion_index(list);
	//list = expansao
	list = ms_quotes_off(list);
	return (list);
}