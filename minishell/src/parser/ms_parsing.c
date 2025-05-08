/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:15:36 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/05/08 18:46:44 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_parsing(char *input)
{
	t_token		*list;

	list = NULL;
	list = ms_tokenization(input, list);
	ms_print_list(list);
}

bool ms_check_expansion(char *input, t_token_type type)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && type != 9)
			return (true);
		i++;
	}
	return (false);
}