/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:03:26 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/11 14:06:22 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ms_main_parsing(char *input, t_minishell *data)
{
	t_token	*tokens;
	t_ast	*ast_tree;
	
	(void)data;
	//(void)ast_tree; // -> delete
	tokens = ms_tokenization(input);
	// ms_print_tokens(tokens);
	ast_tree = ms_parse_tokens(&tokens);
	// print_ast(ast_tree, 0);
	ms_prepare_heredocs(ast_tree);
	ms_exec_tree(ast_tree, data);
	ms_clean_heredocs(ast_tree);
}

void print_indent(int level)
{
	for (int i = 0; i < level; i++)
		printf("  ");
}

const char *get_token_type_name(t_token_type type)
{
	switch (type)
	{
		case TOKEN_INFILE: return "INFILE";
		case TOKEN_OUTFILE: return "OUTFILE";
		case TOKEN_CMD: return "CMD";
		case TOKEN_PIPE: return "PIPE";
		case TOKEN_REDIR_IN: return "REDIR_IN";
		case TOKEN_REDIR_OUT: return "REDIR_OUT";
		case TOKEN_APPEND: return "APPEND";
		case TOKEN_HEREDOC: return "HEREDOC";
		case TOKEN_EOF: return "EOF";
		default: return "UNKNOWN";
	}
}

void print_ast(t_ast *node, int level)
{
	if (!node)
		return;

	print_indent(level);
	printf("Node Number: %d\n", node->node_nbr);      // <-- added this line
	print_indent(level);
	printf("Node Type: %s\n", get_token_type_name(node->type));

	if (node->args)
	{
		for (int i = 0; node->args[i]; i++)
		{
			print_indent(level + 1);
			printf("Arg[%d]: %s\n", i, node->args[i]);
		}
	}

	if (node->left)
	{
		print_indent(level);
		printf("Left:\n");
		print_ast(node->left, level + 1);
	}

	if (node->right)
	{
		print_indent(level);
		printf("Right:\n");
		print_ast(node->right, level + 1);
	}
}

