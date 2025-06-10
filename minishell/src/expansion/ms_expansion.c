/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:02:55 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/10 17:40:20 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


char **ms_extract_expansion(t_token *token)
{
	int		i;
	int		k;
	char 	*variable;
	char	**expansions;
	
	i = 0;
	k = 0;
	expansions = malloc(ms_nbr_expansions(token->expand_index)) + 1;
	while (token->value[i])
	{
		if (token->value[i] == '$' && ms_is_expandable(token->expand_index, i))
		{
			variable = ms_extract_variable(&token->value[i]);
			expansions[k] = getenv(variable);
			free(variable);
			k++;
		}
		i++;
	}
	return (expansions);
}

char	*ms_new_value(t_token  *token, char **expansions)
{
	
}

t_token	*ms_expansion_main(t_token *tokens)
{
	t_token	*temp;
	char	**expansions;
	char	*new_value;
	
	temp = tokens;
	while (temp)
	{
		if (temp->expand == true)
		{
			expansions = ms_extract_expansion(temp);
			new_value = ms_new_value(temp, expansions);
		}
		temp = temp->next;
	}
	return (tokens);
}