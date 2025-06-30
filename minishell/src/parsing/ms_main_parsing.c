/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:03:26 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/30 14:52:55 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// clears list after parsing
void	ms_main_parsing(char *input, t_minishell *data)
{
	t_token	*tokens;
	t_ast	*ast_tree;

	tokens = ms_tokenization(data, input);
	data->token_list = tokens;
	ast_tree = ms_parse_tokens(&tokens);
	data->tree = ast_tree;
	g_signal = 0;
	ms_prepare_heredocs(ast_tree);
	if (g_signal == SIGINT)
	{
		data->last_exit_status = 130;
		ms_clean_heredocs(data->tree);
		ms_clean_ast(data->tree);
		data->tree = NULL;
		return ;
	}
	data->last_exit_status = ms_exec_tree(ast_tree, data);
	ms_clean_heredocs(data->tree);
	ms_clean_ast(data->tree);
}
