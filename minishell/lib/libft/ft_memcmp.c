/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:25:02 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:19:45 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        memcmp - compare memory areas
** 
** SYNOPSIS
**        #include <string.h>
** 
**        int memcmp(const void *s1, const void *s2, size_t n);
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	i = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
		{
			return (ptr1[i] - ptr2[i]);
		}
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int main()
{
    const char *str1 = "Hello, world!";char
    const char *str2 = "Hello, world!";
    int result = ft_memcmp(str1, str2, strlen(str1));
    printf("Test 1: %s\n", result == 0 ? "Passed" : "Failed");

    const char *str3 = "Hello, world!";
    const char *str4 = "Hello, there!";
    result = ft_memcmp(str3, str4, strlen(str3));
    printf("Test 2: %s\n", result != 0 ? "Passed" : "Failed");

    const char *str5 = "abc";
    const char *str6 = "abd";
    result = ft_memcmp(str5, str6, 3);
    printf("Test 3: %s\n", result < 0 ? "Passed" : "Failed");

    const char *str7 = "abd";
    const char *str8 = "abc";
    result = ft_memcmp(str7, str8, 3);
    printf("Test 4: %s\n", result > 0 ? "Passed" : "Failed");

    const char *str9 = "abc";
    const char *str10 = "ab";
    result = ft_memcmp(str9, str10, 2);
    printf("Test 5: %s\n", result == 0 ? "Passed" : "Failed");

    const char *empty1 = "";
    const char *empty2 = "";
    result = ft_memcmp(empty1, empty2, 0);
    printf("Test 6: %s\n", result == 0 ? "Passed" : "Failed");char
	return (0);
}
*/
