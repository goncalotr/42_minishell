/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:03:38 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/11 17:23:47 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ms_another_double(int i, char *value)
{
	while (value[i])
	{
		if (value[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	ms_count_normal(char *string)
{
	int	i;
	int count;

	count = 0;
	i = 0;
	while (string[i])
	{
		if  (string[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int ms_dollar_count(t_token	*list)
{
	int	i;
	int	count;
	int	inside_double;
	
	inside_double = 0;
	count = 0;
	i = 0;
	while (list->value[i])
	{
		if (list->value[i] == '\"')
			inside_double++;
		if (list->value[i] == '\'' && inside_double % 2 == 0)
		{
			i++;
			while (list->value[i] && list->value[i] != '\'')
				i++;
			if (list->value[i] == '\'')
				i++;
			continue;
		}
		if (list->value[i] == '$')
			count++;
		i++;
	}	
	return (count);
}
