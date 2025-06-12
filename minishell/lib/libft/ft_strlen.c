/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:54:46 by goteixei          #+#    #+#             */
/*   Updated: 2024/10/24 00:54:46 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h> // Include standard library for memory allocation
//#include <stdio.h>  // Include for printf

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
#include "stdio.h"

int main()
{
	printf("String length: %d\n", ft_strlen("hello world"));
	return 0;
}
*/
