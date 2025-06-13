/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_off.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:58:29 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/12 17:48:09 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_new_size(char *value)
{
	int	i;
	int	len;
	int	quote;

	i = 0;
	quote = 0;
	len = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
		{
			if (quote == 0)
			{
				quote = value[i];
				i++;
				continue;
			}
			else if (quote == value[i])
			{
				quote = 0;
				i++;
				continue;
			}
		}
		len++;
		i++;
	}
	return (len);
}

char	*ms_put_new(char *value, char *new_value)
{
	int	i;
	int	k;
	int	quote;

	quote = 0;
	i = 0;
	k = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
		{
			if (quote == 0)
			{
				quote = value[i];
				i++;
				continue;
			}
			else if (quote == value[i])
			{
				quote = 0;
				i++;
				continue;
			}
		}
		new_value[k] = value[i];
		k++;
		i++;
	}
	new_value[k] = '\0';
	return (new_value);
}

t_token *ms_quotes_off(t_token *list)
{
	t_token *temp;
	int		new_size;
	char	*new_value;

	temp = list;
	while (temp)
	{
		if((temp->state == DOUBLE_QUOTES || temp->state == SIMPLE_QUOTES) 
			&& temp->type == TOKEN_CMD)
		{
			temp = temp->next;
			continue;
		}
		new_size = ms_new_size(temp->value);
		new_value = malloc(new_size + 1);
		if (!new_value)
			exit(EXIT_FAILURE);
		new_value = ms_put_new(temp->value, new_value);
		free(temp->value);
		temp->value = new_value;
		temp = temp->next;
	}
	return (list);	
}
