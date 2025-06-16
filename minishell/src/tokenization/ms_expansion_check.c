/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:02:33 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/15 16:24:41 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	*ms_expansion_index(char *value, int *index)
{
	int	quote;
	int	i;
	int	k;
	
	k = 0;
	i = 0; 
	quote = 0;
	while (value[i])
	{
		if (ms_is_quote(value[i]) && !quote)
			quote = value[i];
		else if (ms_is_quote(value[i]) && quote == value[i])
			quote = 0;
		if (value[i] == '$' && (quote == 0 || quote == '\"'))
		{
			index[k] = i;
			k++;
		}
		i++;
	}
	index[k] = -1;
	return (index);
}

int ms_expansion_count(char *value)
{
	int	i;
	int	count;
	int	quote;
	
	quote = 0;
	i = 0;
	count = 0;
	while (value[i])
	{
		if (ms_is_quote(value[i]) && !quote)
			quote = value[i];
		else if (ms_is_quote(value[i]) && quote == value[i])
			quote = 0;
		if (value[i] == '$' && (quote == 0 || quote == '\"'))
			count++;
		i++;
	}
	return (count);
}

void ms_expansion_search(t_token *list)
{
	int	*index;
	int	count;

	count = ms_expansion_count(list->value);
	if (count == 0)
		return ;
	list->expand = true;
	index = malloc((count + 1) * sizeof(int));
	if (!index)
		exit(EXIT_FAILURE);
	index = ms_expansion_index(list->value, index);
	list->expand_index = index;
}

t_token	*ms_expansion_check(t_token *list)
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
		ms_expansion_search(temp);
		temp = temp->next;
	}
	return (list);
}
