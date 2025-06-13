/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:05 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/13 20:26:17 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

t_token	*ms_eof_node(t_token *list, char * input, int *i)
{
	char 	*eof;
	int		x;
	
	ms_skip_whitespaces(i, input);
	x = (*i);
	while (input[x] && !(input[x] == 32 || (input[x] >= 7 && input[x] <= 13)))
		x++;
	eof = malloc((x - (*i)) + 1);
	if (!eof)
		return (NULL);
	x = 0;
	while (input[*i] && !(input[*i] == 32 || (input[*i] >= 7 && input[*i] <= 13)))
	{
		eof[x] = input[*i];
		(*i)++;
		x++;
	}
	eof[x] = '\0';
	list = ms_append_node(list, eof, TOKEN_EOF);
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
		list = ms_eof_node(list, input, i);
		return (list);
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		list = ms_append_node(list, ">>", TOKEN_APPEND);
		*i += 2;
		list = ms_eof_node(list, input, i);
		return (list);
	}
	else if (input[*i] == '<')
		list = ms_append_node(list, "<", TOKEN_REDIR_IN);
	else if (input[*i] == '>')
		list = ms_append_node(list, ">", TOKEN_REDIR_OUT);
	(*i)++;
	return list;
}
