/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:15:36 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/13 15:12:30 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_parsing(char *input)
{
	t_token		*list;

	list = NULL;
	list = ms_tokenization(input, list);
	list = ms_check_eof(list);
	list = ms_expansion(list);
	ms_print_list(list);
}

t_token *ms_check_eof(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (temp)
	{
		if (temp->type == TOKEN_HEREDOC && temp->next)
			temp->next->type = TOKEN_EOF;
		temp = temp->next;
	}
	return (list);
}

void	ms_normal_expansion(t_token *list)
{
	int		i;
	int		k;
	int		*index;
	int		count;
	
	i = 0;
	k = 0;
	count = ms_count_dollar(list->value);
	if (count == 0)
		return ;
	index = malloc(count * sizeof(int) + 1);
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

t_token	*ms_expansion(t_token *list)
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
		ms_normal_expansion(temp);
		temp = temp->next;
	}
	return (list);
}

int	ms_count_dollar(char *string)
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
