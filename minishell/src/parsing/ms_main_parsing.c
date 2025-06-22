/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:03:26 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/22 18:00:57 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_main_parsing(char *input, t_minishell *data)
{
	t_token	*tokens;
	t_ast	*ast_tree;

	tokens = ms_tokenization(data, input);
	data->token_list = tokens;
	ast_tree = ms_parse_tokens(&tokens);
	data->tree = ast_tree;
	ms_prepare_heredocs(ast_tree); 
	data->last_exit_status = ms_exec_tree(ast_tree, data);
	ms_clean_heredocs(data->tree);
	ms_clean_ast(data->tree);
	rl_clear_history();
}
