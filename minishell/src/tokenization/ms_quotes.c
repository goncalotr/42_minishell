/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/05/14 13:02:33 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/08 15:50:31 by goteixei         ###   ########.fr       */
=======
/*   Created: 2025/05/14 14:58:29 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/15 17:37:48 by jpedro-f         ###   ########.fr       */
>>>>>>> feature/parsing-main
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_new_value_len(char *value)
{
	int	i;
	int	len;
	int	quote;

	i = 0;
	quote = 0;
	len = 0;
	while (value[i])
	{
		if (ms_is_quote(value[i]) && !quote)
		{
			quote = value[i];
			i++;
			continue;
		}
		else if (ms_is_quote(value[i]) && quote == value[i])
		{
			quote = 0;
			i++;
			continue;
		}
		len++;
		i++;
	}
	return (len);
}

char	*ms_put_new_value(char *value, char *new_value)
{
	int	i;
	int	k;
	int	quote;

	i = 0;
	quote = 0;
	k = 0;
	while (value[i])
	{
		if (ms_is_quote(value[i]) && !quote)
		{
			quote = value[i];
			i++;
			continue;
		}
		else if (ms_is_quote(value[i]) && quote == value[i])
		{
			quote = 0;
			i++;
<<<<<<< HEAD
			while (list->value[i] != '\"' && list->value[i] && ms_another_double(i, list->value))
			//while (list->value[i] != '\"' && list->value[i])
			{
				if (list->value[i] == '$')
				{
					list->expand = true;
					index[k] = i;
					k++;
				}
				i++;
			}
=======
			continue;
>>>>>>> feature/parsing-main
		}
		new_value[k++] = value[i++];
	}
	new_value[k] = '\0';
	return (new_value);
}

char	*ms_quotes_off(char *value)
{
	int		new_value_len;
	char	*new_value;

	new_value_len = ms_new_value_len(value);
	new_value = malloc(new_value_len + 1);
	if (!new_value)
		return NULL;
	new_value = ms_put_new_value(value, new_value);
	free(value);
	return (new_value);
}

t_token *ms_handle_quotes(t_token *list)
{
	t_token *temp;

	temp = list;
	while (temp)
	{
		if (temp->type >= 3 && temp->type <= 7)
		{
			temp = temp->next;
			continue;
		}
		if (temp->type == TOKEN_CMD)
		{
			temp = ms_quotes_cmd(temp);
			temp = temp->next;
			continue;
		}
		temp->value = ms_quotes_off(temp->value);
		temp = temp->next;
	}
	return (list);	
}
