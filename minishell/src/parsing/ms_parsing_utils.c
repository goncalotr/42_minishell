/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:12:32 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/20 17:35:49 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*ms_new_ast_node(t_token_type type)
{
	t_ast		*node;
	static int	node_nbr = 0;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->node_nbr = node_nbr++;
	node->file_name = NULL;
	return (node);
}

t_ast	*ms_create_and_link_redir(t_token **token_list)
{
	t_ast	*redirect_node;
	t_token	*file_token;
	t_token	*redir_token;

	redir_token = (*token_list);
	file_token = redir_token->next;
	(*token_list) = file_token->next;
	redirect_node = ms_new_ast_node(redir_token->type);
	redirect_node->right = ms_create_file_node(file_token);
	redirect_node->left = ms_parse_redirection(token_list);
	free(redir_token->value);
	free(redir_token);
	return (redirect_node);
}

char	**ms_cpy_array(char **src)
{
	int		len;
	char	**dest;
	int		i;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	dest = malloc(sizeof(char *) * (len + 1));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	ms_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
