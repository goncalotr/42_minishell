/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:37:29 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/14 15:16:26 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ms_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return true;
	else
		return false;
}

bool	ms_ismetachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

bool	ms_isspace(char c)
{
	if (c == 32 || (c >= 7 && c <= 13))
		return (true);
	else
		return (false);
}

bool	ms_is_infile(t_token *list)
{
	t_token	*last_node;
	
	last_node = ms_last_node(list);
	if(last_node->type == TOKEN_REDIR_IN)
		return (true);
	else
		return (false);
}

bool	ms_is_file(t_token	*list)
{
	t_token	*last_node;
	
	last_node = ms_last_node(list);
	if (last_node == NULL)
		return (false);
	if(last_node->type == TOKEN_REDIR_IN || 
		last_node->type == TOKEN_REDIR_OUT || 
			last_node->type == TOKEN_APPEND)
		return (true);
	else
		return (false);
}
