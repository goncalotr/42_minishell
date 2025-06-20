/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_export_print.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:53:49 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/20 16:13:38 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Sorts the given string array in place using bubble sort.
 */
static void	ms_sort_env_copy(char **copy, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (ft_strcmp(copy[j], copy[j + 1]) > 0)
			{
				tmp = copy[j];
				copy[j] = copy[j + 1];
				copy[j + 1] = tmp;
			}
		}
	}
}

/**
 * @brief Creates a sorted duplicate of the shell's environment list.
 */
static char	**ms_create_sorted_env_copy(t_minishell *data, int count)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (perror("minishell: export (malloc)"), NULL);
	i = -1;
	while (++i < count)
	{
		copy[i] = ft_strdup(data->envp[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			return (free(copy), NULL);
		}
	}
	copy[count] = NULL;
	ms_sort_env_copy(copy, count);
	return (copy);
}

/**
 * @brief Prints a single environment variable in the `declare -x` format.
 */
static void	ms_print_one_var(const char *env_entry)
{
	const char	*value_ptr;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	value_ptr = ft_strchr(env_entry, '=');
	if (value_ptr)
	{
		write(STDOUT_FILENO, env_entry, value_ptr - env_entry);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		value_ptr++;
		while (*value_ptr)
		{
			if (*value_ptr == '"' || *value_ptr == '$' || *value_ptr == '\\')
				ft_putchar_fd('\\', STDOUT_FILENO);
			ft_putchar_fd(*value_ptr, STDOUT_FILENO);
			value_ptr++;
		}
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putstr_fd(env_entry, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	ms_print_exported_vars(t_minishell *data)
{
	int		count;
	char	**env_copy;
	int		i;

	count = 0;
	if (data->envp)
	{
		while (data->envp[count])
			count++;
	}
	if (count == 0)
		return (0);
	env_copy = ms_create_sorted_env_copy(data, count);
	if (!env_copy)
		return (1);
	i = 0;
	while (i < count)
	{
		ms_print_one_var(env_copy[i]);
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
	return (0);
}
