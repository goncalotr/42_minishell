/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:04:44 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 18:18:58 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Helper function to free the array returned by ft_split
static void	ms_free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

// Helper function to join directory and command name safely
static char	*ms_join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full_path;

	if (dir && dir[0] != '\0')
		tmp = ft_strjoin(dir, "/");
	else
		tmp = ft_strdup("");
	if (!tmp)
	{
		perror("minishell: join_path (strdup/strjoin)");
		return (NULL);
	}
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
	{
		perror("minishell: join_path (strjoin)");
		return (NULL);
	}
	return (full_path);
}

static char	*ms_get_path_variable(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

static char	*ms_find_command_path_help(const char *cmd, char **envp)
{
	char	*path_env_value;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			else
				errno = ENOENT;
		}
		else
			errno = ENOENT;
		return (NULL);
	}
	path_env_value = ms_get_path_variable(envp);
	if (!path_env_value)
		return (NULL);
	return (path_env_value);
}

/**
 * @brief Finds the full path of a command using the PATH environment variable.
 * @param cmd The command name (e.g., "ls").
 * @param envp The environment array.
 * @return Allocated string containing the full path if found and executable,
 *         NULL otherwise (or on error).
 *         The caller must free the returned string.
 * 
 * 1 Handle absolute paths
 * 2 Find PATH variable in PATH
 * 3 Split PATH variable into directories
 * 4 Iterate through directories and check the command
 * 5 Command not found in any PATH directory
 * 
 * F_OK - exists and is executable
 * X_OK
 */
char	*ms_find_command_path(const char *cmd, char **envp)
{
	char	*path_info;
	char	**paths;
	char	*full_path;
	int		i;

	path_info = ms_find_command_path_help(cmd, envp);
	if (!path_info)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (path_info);
	paths = ft_split(path_info, ':');
	if (!paths)
		return (perror("minishell: ft_split (PATH)"), NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ms_join_path(paths[i], cmd);
		if (!full_path)
			return (ms_free_paths(paths), NULL);
		if (access(full_path, X_OK) == 0)
			return (ms_free_paths(paths), full_path);
		free(full_path);
		i++;
	}
	return (ms_free_paths(paths), NULL);
}
