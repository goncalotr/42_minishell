/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:51:13 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/05 16:14:29 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool ms_syntax_check(char *input_line)
{
	bool	error;
	char	*input;

	input = ms_remove_whitespaces(input_line);
	if((error = ms_unclosed_quotes(input)) == true)
	{
		ft_putstr_fd("Syntax error: unclosed quotes\n", 2);
		return (error);
	}
	if((error = ms_pipes_placement(input)) == true)
	{
		ft_putstr_fd("Syntax error: misplaced pipes\n", 2);
		return (error);
	}
	if((error = ms_rediractions_placement(input)) == true)
	{
		ft_putstr_fd("Syntax error: misplaced rediractions\n", 2);
		return(error);
	}
	return (false);
}

bool ms_unclosed_quotes(char *input)
{
	int quote_type;
	int	i;

	i = 0;
	quote_type = 0;
	while(input[i])
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

bool ms_pipes_placement(char *input)
{
	int i;
	int	pipe;

	pipe = 0;
	i = ft_strlen(input);
	if ((input[0] == '|') || (input[i - 1] == '|'))
		return (true);
	i = 0;
	while (input[i])
	{
		ms_skip_whitespaces(&i, input);
		ms_skip_inside_quotes(&i, input);
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

bool ms_rediractions_placement(char *input)
{
	int	x;
	int i;

	i = 0;
	x = ft_strlen(input) - 1;
	if (input[x] == '<' || input[x] == '>')
		return (true);
	x = 0;
	i = 0;
	while (input[i])
	{
		ms_skip_whitespaces(&i, input);
		ms_skip_inside_quotes(&i, input);
		if (input[i] == '>')
		{
			i++;
			if (input[i] == '>')
				i++;
			ms_skip_whitespaces(&i, input);
			if ((input[i] == '>') || (input[i] == '<'))
				return (true);
		}
		if (input[i] == '<')
		{
			i++;
			if (input[i] == '<')
				i++;
			ms_skip_whitespaces(&i, input);
			if ((input[i] == '>') || (input[i] == '<'))
				return (true);
		}
		i++;
	}
	return (false);
}
