/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:31:46 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 12:56:25 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ms_update_path(t_minishell *data)
{
	if (data->paths)
	{
		ms_free_data_paths(data->paths);
		data->paths = NULL;
	}
	data->paths = get_path(data->envp);
	return (0);
}

static int	ms_process_single_unset_arg(const char *arg, t_minishell *data,
	bool *path_was_unset)
{
	int	var_index;

	if (!ms_valid_identifier(arg))
	{
		ms_print_invalid_identifier_err(arg);
		return (1);
	}
	var_index = ms_find_env_var_index_unset(arg, data->envp);
	if (var_index != -1)
	{
		if (ft_strcmp(arg, "PATH") == 0)
			*path_was_unset = true;
		ms_remove_env_var_at_index(var_index, data);
	}
	return (0);
}

int	ms_execute_unset(char **args, t_minishell *data)
{
	int		i;
	int		exit_status;
	bool	path_was_unset;

	exit_status = 0;
	path_was_unset = false;
	i = 1;
	while (args[i])
	{
		if (ms_process_single_unset_arg(args[i], data, &path_was_unset) != 0)
			exit_status = 1;
		i++;
	}
	if (path_was_unset)
		ms_update_path(data);
	return (exit_status);
}
