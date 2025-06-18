/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:55:22 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/17 17:29:11 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ms_free_token(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return;
	free(token->value);
	if (token->args)
	{
		while (token->args[i])
		{
			free(token->args[i]);
			i++;
		}
		free(token->args);
	}
	free(token->expand_index);
	free(token);
}

void	ms_clean_token_list(t_token *token)
{
	t_token	*temp;
	
	if (!token)
		return ;
	while (token)
	{
		temp = token->next;
		free(token);
		token = temp;
	}
}

void ms_clean_ast(t_ast *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	ms_clean_ast(node->left);
	ms_clean_ast(node->right);
	if (node->args)
	{
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);		
	}
	if (node->file_name)
		free(node->file_name);
	free(node);
}

void	ms_cleanup_shell(t_minishell *data)
{
	if (data->stdin_fd != -1)
		close(data->stdin_fd);
	if (data->stdout_fd != -1)
		close(data->stdout_fd);
	if (data->stderr_fd != -1)
		close(data->stderr_fd);
	free(data->shell_name);
	ms_free_envp_copy(data->envp);
	ms_free_data_paths(data->paths);
}

void	ms_free_envp_copy(char **envp)
{
	int	i;

	if (!envp)
		return;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	ms_free_data_paths(char **paths)
{
	int	i;

	if (!paths)
		return;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	ms_clean_all(t_minishell *data)
{
	ms_clean_heredocs(data->tree);
	ms_clean_ast(data->tree);
	ms_clean_token_list(data->token_list);
	ms_cleanup_shell(data);
	clear_history();
}