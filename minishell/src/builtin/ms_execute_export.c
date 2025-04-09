/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:33:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/09 01:45:08 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//todo needs linkedlist?


/**
 * @brief Executes the export builtin command.
 *
 * Adds/updates variables in the environment or lists them.
 * Manages the environment via a pointer to the envp array.
 *
 * @param args Arguments array (args[0] is "export").
 * @param envp_ptr Pointer to the shell's environment array pointer.
 * @return int 0 on success, 1 if any identifier was invalid.
 */
int ms_execute_export(char **args, char ***envp_ptr)
{
	int	i;
	int	ret_status;

	return (ret_status);
}
