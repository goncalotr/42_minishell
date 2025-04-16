/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:51:13 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/04/12 17:15:11 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool ms_syntax_check(t_tokens *list)
{
	bool	error;
	
	if((error = ms_unclosed_quotes(list)) == true)
		return (error);
	if((error = ms_pipes_placement(list)) == true)
		return (error);
	return (false);
}

bool ms_unclosed_quotes(t_tokens *list)
{
	int	singl;
	int doubl;
	int	i;

	singl = 0;
	doubl = 0;
	i = 0;
	while (list)
	{
		i = 0;
		while (list->token[i])
		{
			if (list->token[i] == 34)
				doubl++;
			if (list->token[i] == 39)
				singl++;
			i++;
		}
		list = list->next;
	}
	if (singl % 2 == 0 && doubl % 2 == 0)
		return (false);
	else
	{
		ft_putstr_fd("syntax error: unclosed quotes", 2);
		return (true);
	}
}

bool ms_pipes_placement(t_tokens *list)
{
	t_tokens	*last_node;

	if (ft_strncmp(list->token, "|", 1))
	{
		ft_putstr_fd("syntax error: misplaced pipe", 2);
		return (true);
	}
	last_node = ms_last_node(list);
	if (ft_strncmp(last_node->token, "|", 1))
	{
		ft_putstr_fd("syntax error: misplaced pipe", 2);
		return (true);	
	}
	return (false);
}
