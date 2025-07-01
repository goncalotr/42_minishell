/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:53:21 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 13:53:46 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

static void	ms_read_heredoc_input(int fd, const char *limiter)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || g_signal == SIGINT)
		{
			if (line)
				free(line);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

void	ms_exec_heredoc(t_ast *node)
{
	int		fd;
	char	*limiter;
	int		original_stdin;

	if (!node || !node->file_name)
		return ;
	original_stdin = dup(STDIN_FILENO);
	ms_signal_handlers_set_heredoc();
	limiter = node->right->args[0];
	fd = open(node->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("error heredoc");
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		return ;
	}
	g_signal = 0;
	ms_read_heredoc_input(fd, limiter);
	close(fd);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	ms_signal_handlers_set_interactive();
	if (g_signal == SIGINT)
		unlink(node->file_name);
}
