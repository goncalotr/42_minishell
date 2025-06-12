/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:42:00 by goteixei          #+#    #+#             */
/*   Updated: 2024/10/27 18:37:36 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// bzero, explicit_bzero - zero a byte string

#include "libft.h"

void	*ft_bzero(void *s, size_t len)
{
	char	*p;

	p = (char *)s;
	while (len > 0)
	{
		p[len - 1] = '\0';
		len--;
	}
	return (s);
}

/*
#include <string.h>
#include <stdio.h>

int main()
{
    char str[50] = "Test1234567890text for bzero function";
    printf("\nBefore memset(): %s\n", str);

    // Fill some characters of the string
    ft_bzero(str + 5, '.', sizeof(char));
 
    printf("\nAfter ft_bzero(): %s\n", str);
    return (0);
}
*/
