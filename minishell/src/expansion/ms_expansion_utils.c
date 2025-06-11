/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:36:14 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/11 14:04:13 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_nbr_expansions(int *array)
{
	int	nbr;

	nbr = 0;
	while (array[nbr])
		nbr++;
	return (nbr);
}

char *ms_extract_variable(char *string)
{
	int		i;
	int		variable_len;
	char	*variable;

	i = 1;
	variable_len = 0;
	while (string[i] && string[i] != '$' && !ms_isspace(string[i]))
		variable_len++;
	variable = malloc(variable_len + 1);
	if (!variable)
		return (NULL);
	i = 0;
	while (string[i + 1] && string[i + 1] != '$' && !ms_isspace(string[i + 1]))
	{
		variable[i] = string[i + 1];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

bool	ms_is_expandable(int  *array, int index)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i] == index)
			return (true);
		i++;
	}
	return (false);
}

