/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:51:13 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/20 11:56:41 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ms_syntax_check(char *input_line)
{
	char	*input;

	input = ms_remove_whitespaces(input_line);
	if ((ms_unclosed_quotes(input)) == true)
	{
		free(input);
		ft_putstr_fd("Syntax error: unclosed quotes\n", 2);
		return (true);
	}
	else if ((ms_not_required(input_line)) == true)
	{
		free(input);
		ft_putstr_fd("error: characters not required by the subject\n", 2);
		return (true);
	}
	return (ms_syntax_check2(input));
}

bool	ms_syntax_check2(char *input)
{
	if ((ms_pipes_placement(input)) == true)
	{
		free(input);
		ft_putstr_fd("Syntax error: misplaced pipes\n", 2);
		return (true);
	}
	else if ((ms_rediractions_placement(input, 0)) == true)
	{
		free(input);
		ft_putstr_fd("Syntax error: misplaced rediractions\n", 2);
		return (true);
	}
	else if (ms_redir_pipe(input, 0) == true)
	{
		free(input);
		ft_putstr_fd("Syntax error: misplaced pipes\n", 2);
		return (true);
	}
	free(input);
	return (false);
}

bool	ms_unclosed_quotes(char *input)
{
	int	quote_type;
	int	i;

	i = 0;
	quote_type = 0;
	while (input[i])
	{
		if ((input[i] == '\"') || (input[i] == '\''))
		{
			if (quote_type == 0)
				quote_type = input[i];
			else if (quote_type == input[i])
				quote_type = 0;
		}
		i++;
	}
	if (quote_type == 0)
		return (false);
	else
		return (true);
}

bool	ms_pipes_placement(char *input)
{
	int	i;
	int	pipe;

	pipe = 0;
	i = ft_strlen(input);
	if ((input[0] == '|') || (input[i - 1] == '|'))
		return (true);
	i = 0;
	while (input[i])
	{
		ms_skip_whitespaces(&i, input);
		if (ms_is_quote(input[i]))
		{
			ms_skip_inside_quotes(&i, input);
			continue ;
		}
		if (input[i] == '|')
			pipe++;
		else
			pipe = 0;
		if (pipe == 2)
			return (true);
		i++;
	}
	return (false);
}

bool	ms_rediractions_placement(char *input, int i)
{
	if (input[ft_strlen(input) - 1] == '<'
		|| input[ft_strlen(input) - 1] == '>')
		return (true);
	while (input[i])
	{
		ms_skip_whitespaces(&i, input);
		if (ms_is_quote(input[i]))
		{
			ms_skip_inside_quotes(&i, input);
			continue ;
		}
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i] == '>' && input[i + 1] == '>')
				i++;
			if (input[i] == '<' && input[i + 1] == '<')
				i++;
			i++;
			ms_skip_whitespaces(&i, input);
			if ((input[i] == '>') || (input[i] == '<'))
				return (true);
		}
		i++;
	}
	return (false);
}
