/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:05 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/16 16:58:35 by jpedro-f         ###   ########.fr       */
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

t_token *ms_extract_operator(char *input, int *i, t_token *list)
{
	if (input[*i] == '|')
		list = ms_append_node(list, "|", TOKEN_PIPE);
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		list = ms_append_node(list, "<<", TOKEN_HEREDOC);
		*i += 2;
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
	return list;
}
