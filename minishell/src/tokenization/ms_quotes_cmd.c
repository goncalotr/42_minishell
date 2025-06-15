/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:11:17 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/15 18:40:43 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_len_args(char *value)
{
	int	len;
	int	i;
	int	quote;

	len = 1;
	i = 0;
	quote = 0;
	while (value[i])
	{
		if (ms_is_quote(value[i]) && !quote)
			quote = value[i];
		else if (ms_is_quote(value[i]) && quote == value[i])
			quote = 0;
		if (ms_isspace(value[i]) && quote == 0)
		{
			len ++;
			i++;
			ms_skip_inside_quotes(&i, value);
			continue;
		}
		i++;
	}
	return (len);
}

t_token	*ms_quotes_cmd(t_token *token)
{
	char	**args;
	
	args = malloc(ms_len_args(token->value) + 1);
	if (!args)
		return NULL;
	return (token);
}