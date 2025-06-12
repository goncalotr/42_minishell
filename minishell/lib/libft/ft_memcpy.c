/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:38:35 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/08 21:51:01 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memcpy - copy memory area

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*temp_dest;
	const char	*temp_src;

	if (!dest && !src)
		return (0);
	temp_dest = (char *)dest;
	temp_src = (const char *)src;
	while (n--)
	{
		*temp_dest++ = *temp_src++;
	}
	return (dest);
}

/*
#include <stddef.h>
#include <stdio.h>

int main()
{
    char str1[] = "Test1234567890text for memset function";
	char str2[100];
    printf("\nSource: %s\n", str1);

    // Function usage
    ft_memcpy(str2, str1, sizeof(str1)+1);
 
    printf("\nDestination using ft_memcpy(): %s\n", str2);
    return (0);
}
*/
