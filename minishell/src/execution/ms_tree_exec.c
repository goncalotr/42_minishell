/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tree_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:43:03 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/09 18:02:08 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ms_exec_heredoc(t_ast *node)
{
	int		fd;
	char	*line;
	char	*limiter;

	if (!node || !node->file_name)
		return ;
	limiter = node->right->args[0];
	fd = open(node->file_name, O_CREAT | O_WRONLY | O_TRUNC , 0644);
	if (fd < 0)
	{
		perror("error heredoc");
		return ;
	}
	while(1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

int	ms_exec_redir_out(t_ast	*node, t_minishell *data)
{
	t_ast 	*cmd;
	t_ast 	*outfile;
	int		fd;
	int		original_std;
	int		status;

	original_std = dup(STDOUT_FILENO);
	cmd = node->left;
	outfile = node->right;
	if (node->type == TOKEN_REDIR_OUT)
		fd = open(outfile->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
 		fd = open(outfile->args[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open outfile");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	status = ms_exec_tree(cmd, data);
	dup2(original_std, STDOUT_FILENO);
	close(original_std);
	return (status);
}
int	ms_exec_redir_in(t_ast *node, t_minishell *data)
{
	t_ast	*cmd;
	t_ast	*infile;
	int		fd;
	int		original_std;
	int		status;
	
	cmd = node->left;
	infile = node->right;
	if (node->type == TOKEN_HEREDOC)
		fd = open(node->file_name, O_RDONLY);
	else
		fd = open(infile->args[0], O_RDONLY);
	if (fd < 0)
	{
		perror("open infile");
		return (1);
	}
	original_std = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	status = ms_exec_tree(cmd, data);
	dup2(original_std, STDIN_FILENO);
	close(original_std);
	return (status);
}

int	ms_exec_pipe(t_ast *node, t_minishell *data)
{
	int	pipefd[2];
	int	pid_1;
	int	pid_2;
	int status;
	
	pipe(pipefd);
	if ((pid_1 = fork()) == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		exit(ms_exec_tree(node->left, data));
	}
	if ((pid_2 = fork()) == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(ms_exec_tree(node->right, data));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, &status, 0);
	return (WEXITSTATUS(status));	
}

int	ms_exec_cmd(t_ast *node, t_minishell *data)
{
	int		i;
	char 	full_path[1024];
	pid_t	pid;
	int		status;
	
	i = 0;
	if ((pid = fork()) == 0)
	{
		if (ft_strchr(node->args[0], '/'))
		{
			if (access(node->args[0], X_OK) == 0)
			{
				execve(node->args[0], node->args, data->envp);
				perror(node->args[0]);
				exit(127);
			}
			perror(node->args[0]);
			exit(127);
		}
		while (data->paths[i])
		{
			ft_strlcpy(full_path, data->paths[i], sizeof(full_path));
			ft_strlcat(full_path, "/", sizeof(full_path));
			ft_strlcat(full_path, node->args[0], sizeof(full_path));
			if (access(full_path, X_OK) == 0)
				execve(full_path, node->args, data->envp);
			i++;
		}
		ms_command_not_found(node->args);
		exit (127);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	ms_exec_tree(t_ast *node, t_minishell *data)
{
	if (!node)
		return 0;
	if (node->type == TOKEN_CMD)
		return (ms_exec_cmd(node, data));
	if (node->type == TOKEN_PIPE)
		return (ms_exec_pipe(node, data));
	if (node->type == TOKEN_REDIR_IN)
		return (ms_exec_redir_in(node, data));
	if (node->type == TOKEN_REDIR_OUT)
		return (ms_exec_redir_out(node, data));
	if (node->type == TOKEN_APPEND)
		return (ms_exec_redir_out(node, data));
	if (node->type == TOKEN_HEREDOC)
		return (ms_exec_redir_in(node, data));
	if (node->type == TOKEN_INFILE || node->type == TOKEN_OUTFILE
		|| node->type == TOKEN_EOF)
		return (0);
	return (1);
}
