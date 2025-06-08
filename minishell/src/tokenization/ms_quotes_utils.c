/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:03:38 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/08 15:33:58 by goteixei         ###   ########.fr       */
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

int ms_quotes_count(t_token	*list)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (list->value[i])
	{
		if (list->value[i] == '\'')
		{
			i++;
			while (list->value[i] != '\''  && list->value[i])
				i++;
		}
		if (list->value[i] == '\"')
		{
			i++;
			//while (list->value[i] != '\"' && list->value[i] && ms_another_double(i, list->value))
			while (list->value[i] != '\"' && list->value[i])
			{
				if (list->value[i] == '$')
					count++;
				i++;
			}
		}
		i++;
	}
	return (count);
}
