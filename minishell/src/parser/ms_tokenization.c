/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:22 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/04/16 18:08:36 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tokens *ms_extract_operator(char *input, int *i, t_tokens *list)
{
	if (input[*i] == '|')
		list = ms_append_node(list, "|", PIPE);
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		list = ms_append_node(list, "<<", HEREDOC);
		*i += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		list = ms_append_node(list, ">>", APPEND);
		*i += 2;
	}
	else if (input[*i] == '<')
		list = ms_append_node(list, "<", IN);
	else if (input[*i] == '>')
		list = ms_append_node(list, ">", OUT);
	(*i)++;
	return list;
}

t_tokens	*ms_extract_word(char *input, int *i, t_tokens *list)
{
	char	*word;
	int 	k;

	word = malloc(1024);
	if (!word)
		return list;
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
	list = ms_append_node(list, word, WORD);
	free(word);
	return (list);
}
void ms_tokenization(char *input)
{
	t_tokens	*list;
	int			i;

	i = 0;
	list =  NULL;
	while (input[i])
	{
		while(input[i] == 32 || (input[i] >= 7 && input[i] <= 13))
			i++;
		if(!input[i])
			break;
		if(input[i] == '|' || (input[i] == '<' || input[i] == '>'))
			list = ms_extract_operator(input, &i, list);
		else
			list =  ms_extract_word(input, &i, list);
	}
	ms_print_list(list);
}																																																
