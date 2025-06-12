/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:38:22 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/08 22:04:51 by goteixei         ###   ########.fr       */
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	while ((dst_len + i) < (size - 1) && (src[i] != '\0'))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}

/*
#include <stdio.h>

int main()
{
	char str1[] = "Test1234567890text for ft_strlcat function";
	char str2[] = "asdsffg....";
	printf("Src: %s\n", str1);

	// Function usage
	ft_strlcat(str2, str1, 8*sizeof(str2));

	printf("Dst: %s\n", str2);
	return (0);
}
*/
