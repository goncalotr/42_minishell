/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:12:03 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 16:06:18 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**      strlcpy, strlcat — size-bounded string copying and concatenation
** 
** LIBRARY
**      Utility functions from BSD systems (libbsd, -lbsd)
** 
** SYNOPSIS
**      #include <string.h>
**      (See libbsd(7) for include usage.)
** 
**      size_t
**      strlcpy(char *dst, const char *src, size_t size);
** 
**      size_t
**      strlcat(char *dst, const char *src, size_t size);
*/

#include "libft.h"

/*
size_t ft_strlen(const char *str)
{
    size_t len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/*
#include <stdio.h>

int main()
{
	char str1[] = "Test1234567890text for ft_strlcpy function";
	char str2[100];
	printf("\nSource: %s\n", str1);

	// Function usage
	ft_strlcpy(str2, str1, sizeof(str2));

	printf("\nDestination using ft_strlcpy(): %s\n", str2);
	return (0);
}
*/
