/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:02:33 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/12 14:56:08 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_normal_index(t_token *list)
{
	int		i;
	int		k;
	int		*index;
	int		count;
	
	i = 0;
	k = 0;
	count = ms_count_normal(list->value);
	if (count == 0)
		return ;
	index = malloc((count + 1) * sizeof(int));
	if (!count)
		exit(EXIT_FAILURE);
	while (list->value[i])
	{
		if (list->value[i] == '$')
		{
			index[k] = i;
			k++;
			list->expand = true;
		}
		i++;
	}
	index[k] = -1;
	list->expand_index = index;
}

int	*ms_put_index(t_token *list, int *index, int i, int k)
{
	int	inside_double;
	
	inside_double = 0;
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
		{
			list->expand = true;
			index[k] = i;
			k++;
		}
		i++;
	}
	return (index);
}

void ms_quotes_index(t_token *list)
{
	int	*index;
	int	count;

	count = ms_dollar_count(list);
	if (count == 0)
		return ;
	index = malloc((count + 1) * sizeof(int));
	if (!index)
		exit(EXIT_FAILURE);
	index = ms_put_index(list, index, 0, 0);
	index[count] = -1;
	list->expand_index = index;
}

t_token	*ms_expansion_index(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (temp)
	{
		if (temp->type >= 3 && temp->type <= 7)
		{
			temp = temp->next;
			continue;
		} 
		// if (temp->state == DOUBLE_QUOTES || temp->state == SIMPLE_QUOTES)
		ms_quotes_index(temp);
		// else
		// 	ms_normal_index(temp);
		temp = temp->next;
	}
	return (list);
}
