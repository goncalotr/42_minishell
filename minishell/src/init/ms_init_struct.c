/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:19:19 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/14 18:19:29 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" // Adjust path as needed

/**
 * @brief Frees the memory allocated for a duplicated environment list.
 *        Handles NULL input gracefully.
 * @param envp_copy The char** list to free.
 */
void free_envp_copy(char **envp_copy)
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
 *         Returns an allocated array containing only NULL if envp is NULL or empty.
 */
char	**duplicate_envp(char **envp)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	// Count existing entries safely, handling NULL envp
	if (envp)
	{
		while (envp[count])
			count++;
	}

	// Allocate space for pointers + 1 for NULL terminator
	copy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!copy)
	{
		perror("minishell: malloc error duplicating envp");
		return (NULL);
	}

	// Duplicate each string
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			// Allocation failed for one string, clean up previously allocated ones
			perror("minishell: ft_strdup error duplicating envp entry");
			free_envp_copy(copy); // Free the array and the strings allocated so far
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL; // Null-terminate the array
	return (copy);
}

/**
 * @brief Initializes the main shell data structure.
 *
 * @param data Pointer to the t_data struct to initialize.
 * @param argv The argument vector from main (for shell_name).
 * @param envp The environment variables from main.
 * @return 0 on success, 1 on failure (e.g., memory allocation, dup error).
 */
int	init_shell_data(t_data *data, char **argv, char **envp)
{
	if (!data || !argv) // Basic validation
		return (1);

	// 1. Initialize pointers to NULL first for safety in cleanup
	data->environ_list = NULL;
	data->shell_name = NULL;
	data->stdin_fd = -1; // Initialize FDs to invalid state
	data->stdout_fd = -1;
	data->stderr_fd = -1;

	// 2. Duplicate environment variables
	data->environ_list = duplicate_envp(envp);
	if (!data->environ_list)
		return (1); // Error message printed by duplicate_envp or malloc

	// 3. Initialize exit status
	data->last_exit_status = 0;

	// 4. Save original standard I/O file descriptors using dup()
	data->stdin_fd = dup(STDIN_FILENO);
	if (data->stdin_fd == -1)
	{
		perror("minishell: dup(STDIN_FILENO)");
		free_envp_copy(data->environ_list); // Clean up allocated env
		return (1);
	}
	data->stdout_fd = dup(STDOUT_FILENO);
	if (data->stdout_fd == -1)
	{
		perror("minishell: dup(STDOUT_FILENO)");
		free_envp_copy(data->environ_list);
		close(data->stdin_fd); // Clean up previously dup'd fd
		return (1);
	}
	data->stderr_fd = dup(STDERR_FILENO);
	if (data->stderr_fd == -1)
	{
		perror("minishell: dup(STDERR_FILENO)");
		free_envp_copy(data->environ_list);
		close(data->stdin_fd);
		close(data->stdout_fd); // Clean up previously dup'd fds
		return (1);
	}

	// 5. Store shell name (duplicate it)
	if (argv[0]) // Check if argv[0] exists
		data->shell_name = ft_strdup(argv[0]);
	else
		data->shell_name = ft_strdup("minishell"); // Default name if argv[0] is NULL

	if (!data->shell_name) {
		perror("minishell: ft_strdup for shell_name");
		free_envp_copy(data->environ_list);
		close(data->stdin_fd);
		close(data->stdout_fd);
		close(data->stderr_fd);
		return (1);
	}

	// 6. Store pointer to original envp (no allocation needed)
	data->envp_original = envp;

	return (0); // Success!
}
