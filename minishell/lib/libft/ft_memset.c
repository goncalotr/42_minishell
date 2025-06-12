/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:43:26 by goteixei          #+#    #+#             */
/*   Updated: 2024/10/25 11:30:30 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memset - fill memory with a constant byte

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	char	*p;

	p = (char *)s;
	while (len > 0)
	{
		p[len - 1] = c;
		len--;
	}
	return (s);
}

/*
#include <string.h>
#include <stdio.h>

int main()
{
    char str[50] = "Test1234567890text for memset function";
    printf("\nBefore memset(): %s\n", str);

    // Fill some characters of the string
    ft_memset(str + 5, '.', sizeof(char));
 
    printf("\nAfter ft_memset(): %s\n", str);
    return (0);
}
*/