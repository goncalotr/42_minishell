/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:35:49 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:15:33 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        strcmp, strncmp - compare two strings
** 
** SYNOPSIS
**        #include <string.h>
** 
**        int strcmp(const char *s1, const char *s2);
** 
**        int strncmp(const char *s1, const char *s2, size_t n);
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char) s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <stddef.h>int	ft_strncmp(const char *s1, const  *s2, size_t n)


int main()
{
    const char *test1 = "Hello";
    const char *test2 = "Hello";
    const char *test3 = "Hello, World!";
    const char *test4 = "Hello";
    const char *test5 = "Hella";
    const char *test6 = "Hello";
    const char *test7 = "HelLo";
    const char *test8 = "Hell";
    const char *test9 = "Hello";
    const char *test10 = "Hello!";
    const char *test11 = "";
    const char *test12 = "Test";

    printf("Test 1: %d\n", ft_strncmp(test1, test2, 5));
    printf("Test 2: %d\n", ft_strncmp(test1, test3, 5));
    printf("Test 3: %d\n", ft_strncmp(test1, test4, 3));
    printf("Test 4: %d\n", ft_strncmp(test1, test5, 5));
    printf("Test 5: %d\n", ft_strncmp(test1, test6, 5));
    printf("Test 6: %d\n", ft_strncmp(test1, test7, 5));
    printf("Test 7: %d\n", ft_strncmp(test1, test8, 4));
    printf("Test 8: %d\n", ft_strncmp(test1, test9, 10));
    printf("Test 9: %d\n", ft_strncmp(test1, test10, 5));
    printf("Test 10: %d\n", ft_strncmp(test11, test12, 0));
	return (0);
}
*/
