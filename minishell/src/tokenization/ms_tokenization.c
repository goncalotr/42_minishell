/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:22 by jpedro-f          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/10 20:02:00 by goteixei         ###   ########.fr       */
=======
/*   Updated: 2025/06/16 13:21:42 by jpedro-f         ###   ########.fr       */
>>>>>>> feature/parsing-main
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
		if (ms_ismetachar(input[x]) && quote == 0)
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
		if ((ms_isspace(input[*i]) || ms_ismetachar(input[*i])) && quote == 0)
				break ;
		token[x] = input[*i];
		(*i)++;
		x++;
	}
	token[x] = '\0';
	return (token);
}

char	*ms_cpy_token_cmd(char *input, int *i)
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
		if (ms_ismetachar(input[*i]) && quote == 0)
				break ;
		token[x] = input[*i];
		(*i)++;
		x++;
	}
	token[x] = '\0';
	return (token);
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
		else 
			list = ms_extract_word(input, &i, list);
	}
	return (list);
}

t_token	*ms_tokenization(t_minishell *data, char *input)
{
	t_token		*tokens;

<<<<<<< HEAD
	list = NULL;
	list = ms_start_tokenization(input, list);
	list = ms_assign_state(list);
	// list = ms_check_eof(list);
	list = ms_expansion_index(list);
	//list = expansao
	list = ms_expand_variables(data, list);
	// list = ms_quotes_off(list);
	return (list);
=======
	tokens = NULL;
	tokens = ms_start_tokenization(input, tokens);
	// tokens = ms_assign_state(tokens);
	tokens = ms_expansion_check(tokens);
	tokens = ms_handle_quotes(tokens);
	return (tokens);
>>>>>>> feature/parsing-main
}
