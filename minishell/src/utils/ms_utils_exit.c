/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:14:59 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/11 01:29:06 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ms_exit_with_code(t_minishell *data, int status)
{
	data->last_exit_status = WEXITSTATUS(status);
	return (data->last_exit_status);
}
