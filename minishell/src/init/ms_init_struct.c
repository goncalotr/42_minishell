/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:19:19 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/01 11:02:29 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" // Adjust path as needed

char	**get_path(char **envp)
{
	int		i;
	char	*path_value;

	i = 0;
	path_value = NULL;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_value = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (path_value == NULL)
		return (NULL);
	return (ft_split(path_value, ':'));
}

/**
 * @brief Frees the memory allocated for a duplicated environment list.
 *        Handles NULL input gracefully.
 * @param envp_copy The char** list to free.
 */
void	free_envp_copy(char **envp_copy)
{
	int	i;

	if (!envp_copy)
		return ;
	i = 0;
	while (envp_copy[i])
	{
		free(envp_copy[i]);
		i++;
	}
	free(envp_copy);
}

/**
 * @brief Duplicates the environment variable array (deep copy).
 *        Handles allocation errors.
 * @param envp The original environment array from main. Can be NULL.
 * @return A newly allocated, NULL-terminated copy of envp, or NULL on failure.
 *         Returns an allocated array containing only NULL if envp is
 * NULL or empty.
 */
char	**duplicate_envp(char **original_envp)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	if (original_envp)
	{
		while (original_envp[count])
			count++;
	}
	copy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (perror("minishell: malloc error duplicating envp"), NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(original_envp[i]);
		if (!copy[i])
			return (perror("minishell: ft_strdup error duplicating envp \
entry"), free_envp_copy(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	init_shell_data_aux1(t_minishell *data, char **envp_main)
{
	data->envp = NULL;
	data->shell_name = NULL;
	data->tree = NULL;
	data->token_list = NULL;
	data->stdin_fd = -1;
	data->stdout_fd = -1;
	data->stderr_fd = -1;
	data->pid = ms_getpid();
	data->envp = duplicate_envp(envp_main);
	if (!data->envp && envp_main)
		return (1);
	data->paths = get_path(data->envp);
	data->last_exit_status = 0;
	data->stdin_fd = dup(STDIN_FILENO);
	if (data->stdin_fd == -1)
		return (perror("minishell: dup(STDIN_FILENO)"), \
free_envp_copy(data->envp), 1);
	data->stdout_fd = dup(STDOUT_FILENO);
	if (data->stdout_fd == -1)
		return (perror("minishell: dup(STDOUT_FILENO)"), \
free_envp_copy(data->envp), close(data->stdin_fd), 1);
	data->stderr_fd = dup(STDERR_FILENO);
	return (0);
}

/**
 * @brief Initializes the main shell data structure.
 *
 * @param data Pointer to the t_data struct to initialize.
 * @param argv The argument vector from main (for shell_name).
 * @param envp The environment variables from main.
 * @return 0 on success, 1 on failure (e.g., memory allocation, dup error).
 * 
 * 1. Initialize pointers to NULL first for safety in cleanup
 * 2. Duplicate environment variables
 * 3. Initialize exit status
 * 4. Save original standard I/O file descriptors using dup()
 * 5. Store shell name (duplicate it)
 * 6. Store pointer to original envp (no allocation needed)
 */
int	init_shell_data(t_minishell *data, char **argv, char **envp_main)
{
	if (init_shell_data_aux1(data, envp_main) != 0)
		return (1);
	if (data->stderr_fd == -1)
	{
		perror("minishell: dup(STDERR_FILENO)");
		free_envp_copy(data->envp);
		close(data->stdin_fd);
		close(data->stdout_fd);
		return (1);
	}
	if (argv[0])
		data->shell_name = ft_strdup(argv[0]);
	else
		data->shell_name = ft_strdup("minishell");
	if (!data->shell_name)
	{
		perror("minishell: ft_strdup for shell_name");
		free_envp_copy(data->envp);
		close(data->stdin_fd);
		close(data->stdout_fd);
		close(data->stderr_fd);
		return (1);
	}
	return (0);
}
