/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:11 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 16:49:11 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

static void	ms_exec_pipe_left(t_ast *node, int pipefd[2], t_minishell *data)
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ms_exec_tree(node->left, data);
	ms_clean_all(data);
	exit(0);
}

static void	ms_exec_pipe_right(t_ast *node, int pipefd[2], t_minishell *data)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ms_exec_tree(node->right, data);
	ms_clean_all(data);
	exit(0);
}

static int	ms_wait_for_pipe_children(int pid_1, int pid_2)
{
	int	status_1;
	int	status_2;
	int	final_exit_status;

	waitpid(pid_1, &status_1, 0);
	waitpid(pid_2, &status_2, 0);
	if (WIFEXITED(status_2))
		final_exit_status = WEXITSTATUS(status_2);
	else if (WIFSIGNALED(status_2))
	{
		final_exit_status = 128 + WTERMSIG(status_2);
		if (WTERMSIG(status_2) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
	else
		final_exit_status = 1;
	return (final_exit_status);
}

int	ms_exec_pipe(t_ast *node, t_minishell *data)
{
	int	pipefd[2];
	int	pid_1;
	int	pid_2;
	int	exit_status;

	ms_signal_handlers_set_non_interactive();
	if (pipe(pipefd) == -1)
		return (perror("pipe"), ms_signal_handlers_set_interactive(), 1);
	pid_1 = fork();
	if (pid_1 == -1)
		return (ms_signal_handlers_set_interactive(), perror("fork"), 1);
	if (pid_1 == 0)
		ms_exec_pipe_left(node, pipefd, data);
	pid_2 = fork();
	if (pid_2 == -1)
		return (ms_signal_handlers_set_interactive(), perror("fork"), 1);
	if (pid_2 == 0)
		ms_exec_pipe_right(node, pipefd, data);
	close(pipefd[0]);
	close(pipefd[1]);
	exit_status = ms_wait_for_pipe_children(pid_1, pid_2);
	ms_signal_handlers_set_interactive();
	return (exit_status);
}
