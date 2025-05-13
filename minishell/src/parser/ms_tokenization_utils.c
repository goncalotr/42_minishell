/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:05 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/09 15:37:06 by jpedro-f         ###   ########.fr       */
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
		if(input[i] == quote_type)
		{
			if(input[i + 1] == '\'' || input[i + 1] == '\"')
			{
				i++;
				len++;
				quote_type = input[i];
			}
			else
				break;  	
		}
		len++;
		i++;
	}
	return (len);
}

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
