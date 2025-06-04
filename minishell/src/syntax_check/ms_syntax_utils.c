/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:43:34 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/02 12:57:54 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_remove_whitespaces(char	 *input_line)
{
	int		start;
	int		finish;
	char	*input;
	int		i;

	i = 0;
	start = 0;
	finish = ft_strlen(input_line) - 1;
	while ((input_line[start] == 32) || (input_line[start] >= 7 && input_line[start] <= 13))
		start++;
	while ((input_line[finish] == 32) || (input_line[finish] >= 7 && input_line[finish] <= 13))
		finish--;
	input = malloc((finish - start) + 1);
	while (start <= finish)
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
	if (input[*i] == 34)
	{
		(*i)++;
		while (input[*i] && input[*i] != 34 && input[*i + 1] != 34)
			(*i)++;
	}
	if (input[*i] == 39)
	{
		(*i)++;
		while (input[*i] && input[*i] != 39 && input[*i + 1] != 39)
			(*i)++;
	}
	(*i)++;
}

void	ms_skip_whitespaces(int *i, char *input)
{
	while (input[*i] && (input[*i] == 32 || (input[*i] >= 7 && input[*i] <= 13)))
		(*i)++;
}
