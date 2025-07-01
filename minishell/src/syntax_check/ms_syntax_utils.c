/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:43:34 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/30 14:53:53 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_remove_whitespaces(char *input_line)
{
	int		start;
	int		finish;
	char	*input;
	int		i;

	i = 0;
	start = 0;
	finish = ft_strlen(input_line);
	ms_skip_whitespaces(&start, input_line);
	if (start == finish)
		return (NULL);
	while ((input_line[finish - 1] == 32)
		|| (input_line[finish - 1] >= 7 && input_line[finish - 1] <= 13))
		finish--;
	input = malloc((finish - start) + 1);
	if (!input)
		return (NULL);
	while (start <= finish - 1)
	{
		input[i] = input_line[start];
		start++;
		i++;
	}
	input[i] = '\0';
	return (input);
}

void	ms_skip_inside_quotes(int *i, char *input)
{
	if (!input[*i])
		return ;
	if (input[*i] == '\"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\"')
			(*i)++;
		if (input[*i] == '\"')
			(*i)++;
	}
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (input[*i] == '\'')
			(*i)++;
	}
}

void	ms_skip_whitespaces(int *i, char *input)
{
	while (input[*i] && (input[*i] == 32
			|| (input[*i] >= 7 && input[*i] <= 13)))
		(*i)++;
}

bool	ms_not_required(char *input)
{
	int	quote_type;
	int	i;

	i = 0;
	quote_type = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (quote_type == 0)
				quote_type = input[i];
			else if (quote_type == input[i])
				quote_type = 0;
		}
		if ((input[i] == '\\' || input[i] == ';') && quote_type == 0)
			return (true);
		else if ((input[i] == '&' || (input[i] == '|' && input[i + 1] == '|'))
			&& quote_type == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	ms_redir_pipe(char *input, int i)
{
	while (input[i])
	{
		ms_skip_whitespaces(&i, input);
		if (ms_is_quote(input[i]))
			ms_skip_inside_quotes(&i, input);
		else if (input[i] == '<' || input[i] == '>')
		{
			if ((input[i] == '<' && input[i + 1] == '<')
				|| (input[i] == '>' && input[i + 1] == '>'))
				i++;
			i++;
			ms_skip_whitespaces(&i, input);
			if (input[i] == '|')
				return (true);
		}
		else
			i++;
	}
	return (false);
}
