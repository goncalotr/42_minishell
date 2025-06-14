/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:22 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/14 16:00:31 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_len_token(char *input, int i)
{
	int len;
	int	quote;
	int	x;

	quote = 0;
	x = i;
	while (input[x])
	{
		if(ms_is_quote(input[x]) && !quote)
			quote = input[x];
		else if (ms_is_quote(input[x]) && quote == input[x])
			quote = 0;
		if ((ms_isspace(input[x]) || ms_ismetachar(input[x]))
			&& quote == 0)
				break ;
		x++;
	}
	len = x - i;
	return (len);
}

char	*ms_cpy_token(char *input, int *i)
{
	char 	*token;
	int		x;
	int		quote;
	
	quote = 0;
	x = 0;
	ms_skip_whitespaces(i, input);
	token = malloc(ms_len_token(input, *i) + 1);
	if (!token)
		return (NULL);
	while (input[*i])
	{
		if (ms_is_quote(input[*i]) && !quote)
			quote = input[*i];
		else if (ms_is_quote(input[*i]) && quote == input[*i])
			quote = 0;
		if ((ms_isspace(input[*i]) || ms_ismetachar(input[*i]))
			&& quote == 0)
				break ;
		token[x] = input[*i];
		(*i)++;
		x++;
	}
	token[x] = '\0';
	return (token);
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
