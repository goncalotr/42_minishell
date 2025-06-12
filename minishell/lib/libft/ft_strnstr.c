/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:59:22 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:18:01 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**      strnstr — locate a substring in a string
** 
** LIBRARY
**      Utility functions from BSD systems (libbsd, -lbsd)
** 
** SYNOPSIS
**      #include <string.h>
**      (See libbsd(7) for include usage.)
** 
**      char *
**      strnstr(const char *big, const char *little, size_t len);
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i1] != '\0' && i1 < len)
	{
		if (big[i1] == little[0])
		{
			i2 = 0;
			while ((little[i2] != '\0') && (little[i2] == big[i1 + i2])
				&& (i1 + i2) < len)
			{
				i2++;
			}
			if (little[i2] == '\0')
			{
				return ((char *)(big + i1));
			}
		}
		i1++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main()
{
    const char *haystack1 = "Hello, world!";
    const char *needle1 = "world";
    char *result = ft_strnstr(haystack1, needle1, strlen(haystack1));
    printf("Test 1: %s\n", result != NULL && result == 
	strstr(haystack1, needle1) ? "Passed" : "Failed");

    const char *haystack2 = "abcdef";
    const char *needle2 = "abc";
    result = ft_strnstr(haystack2, needle2, strlen(haystack2));
    printf("Test 2: %s\n", result != NULL && result == 
	strstr(haystack2, needle2) ? "Passed" : "Failed");

    const char *haystack3 = "abcdef";
    const char *needle3 = "def";
    result = ft_strnstr(haystack3, needle3, strlen(haystack3));
    printf("Test 3: %s\n", result != NULL && result == 
	strstr(haystack3, needle3) ? "Passed" : "Failed");

    const char *haystack4 = "abcdef";
    const char *needle4 = "xyz";
    result = ft_strnstr(haystack4, needle4, strlen(haystack4));
    printf("Test 4: %s\n", result == NULL ? "Passed" : "Failed");

    const char *haystack5 = "abcdef";
    const char *needle5 = "cde";
    result = ft_strnstr(haystack5, needle5, 4);
    printf("Test 5: %s\n", result == NULL ? "Passed" : "Failed");

    const char *haystack6 = "abcdef";
    const char *needle6 = "";
    result = ft_strnstr(haystack6, needle6, strlen(haystack6));
    printf("Test 6: %s\n", result != NULL && 
	result == haystack6 ? "Passed" : "Failed");

    const char *haystack7 = "";
    const char *needle7 = "a";
    result = ft_strnstr(haystack7, needle7, strlen(haystack7));
    printf("Test 7: %s\n", result == NULL ? "Passed" : "Failed");

    const char *haystack8 = "short";
    const char *needle8 = "shorter";
    result = ft_strnstr(haystack8, needle8, 10);
    printf("Test 8: %s\n", result == NULL ? "Passed" : "Failed");

	return (0);
}
*/
