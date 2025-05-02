/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:22 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/02 15:37:09 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Extracts a shell operator token (like pipe or redirection) from the input and appends it to the token list.
 *
 * This function checks the current character in the input string to determine
 * if it is a shell operator: `|`, `<`, `>`, `<<`, or `>>`. It then creates the
 * appropriate token and appends it to the token list with the correct type.
 * The index is updated accordingly, especially for double-character operators.
 * 
 * @param input The full input string being tokenized.
 * @param i A pointer to the current index in the input string; gets updated.
 * @param list The existing token list to append the operator token to.
 * 
 * @return The updated token list with the new operator token added.
 */
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

int	ms_len_word(char *input, int i)
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

/**
 * @brief Extracts a word token from the input and appends it to the token list.
 *
 * This function reads characters from the input string starting at the current
 * index, stopping at whitespace or shell metacharacters (`|`, `<`, `>`). 
 * The extracted word is then added to the token list as a `WORD` type token.
 * 
 * @param input The full input string being tokenized.
 * @param i A pointer to the current index in the input string; gets updated.
 * @param list The existing token list to append the word token to.
 * 
 * @return The updated token list with the new word token added.
 */
t_token	*ms_extract_word(char *input, int *i, t_token *list)
{
	char	*word;
	int 	k;

	
	word = malloc(ms_len_word(input, *i) + 1);
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
	list = ms_append_node(list, word, TOKEN_WORD);
	free(word);
	return (list);
}

/**
 * @brief Tokenizes the input string into a linked list of shell tokens.
 *
 * This function processes the given input line, identifying shell operators 
 * (like pipes and redirections) and words, and stores them in a linked
 * list of `t_tokens`. It also skips over whitespace and handles multiple
 * consecutive spaces or tabs.
 * 
 * @param input The raw input line from the user to be tokenized.
 * @param list The existing token list to append to (can be NULL for a fresh list).
 * 
 * @return A pointer to the head of the updated token list.
 */
t_token *ms_tokenization(char *input, t_token *list)
{
	int			i;

	i = 0;
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
	return (list);
}																																																
