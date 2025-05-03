/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:05 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/03 16:24:08 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Calculates the length of the next word token in the input string.
 *
 * This function scans the input from the given index until it hits a shell
 * metacharacter (`|`, `<`, `>`) or a whitespace character (space, tab, newline, etc.).
 * The length of the continuous sequence of regular characters is returned.
 * 
 * @param input The full input string being scanned.
 * @param i The starting index in the input string.
 * 
 * @return The length of the word token found at the given index.
 */

int	ms_len_file(char *input, int i)
{
	int len;

	len = 0;
	while (input[i])
	{
		if(input[i] == 32 || (input[i] >= 7 && input[i] <= 13))
			break;
		if(input[i] == '|' ||  (input[i] == '<' || input[i] == '>'))
			break;
		i++;
		len++;
	}
	return (len);
}

int	ms_len_cmd(char *input, int i)
{
	int len;

	len = 0;
	while (input[i])
	{
		if(input[i] == '|' ||  (input[i] == '<' || input[i] == '>'))
			break;
		i++;
		len++;
	}
	return (len);
}

int ms_quote_len(char *input, int i)
{
	int		len;
	char	quote_type;
	
	quote_type = input[i];
	len = 1;
	i++;
	while (input[i])
	{
		len++;
		if(input[i] == quote_type)
			break;
		i++;
	}
	return (len);
}

bool	ms_is_file(t_token	*list)
{
	t_token	*last_node;
	
	last_node = ms_last_node(list);
	if(last_node->type == 3 || last_node->type == 4 || last_node->type == 5)
		return (true);
	else
		return (false);
}