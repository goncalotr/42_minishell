/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:02:56 by goteixei          #+#    #+#             */
/*   Updated: 2025/02/24 14:43:14 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_error(const int error_code, char *error_message, int fd)
{
	ft_putendl_fd(error_message, fd);
	exit(error_code);
}
