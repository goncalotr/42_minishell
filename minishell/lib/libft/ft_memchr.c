/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:05:10 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:12:57 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        memchr, memrchr, rawmemchr - scan memory for a character
** 
** SYNOPSIS
**        #include <string.h>
** 
**        void *memchr(const void *s, int c, size_t n);
** 
**        void *memrchr(const void *s, int c, size_t n);
** 
**        void *rawmemchr(const void *s, int c);
** 
**    Feature Test Macro Requirements for glibc (see feature_test_macros(7)):
** 
**        memrchr(), rawmemchr(): _GNU_SOURCE
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;
	unsigned char		cha;

	i = 0;
	ptr = (const unsigned char *)s;
	cha = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == cha)
		{
			return ((void *)(ptr + i));
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>

int main()
{
    const char *test_str = "Hello, world!";
    size_t len = strlen(test_str);

    // Test 1: Find a character in the middle
    char *result = ft_memchr(test_str, 'o', len);
	printf("Result: %ld\n", result);
	printf("Test_str: %ld\n", test_str);
    if (result) {
        printf("Test 1 Passed: Found 'o' at position: %ld\n", result - test_str);
    } else {
        printf("Test 1 Failed: 'o' not found.\n");
    }

    // Test 2: Find a character at the beginning
    result = ft_memchr(test_str, 'H', len);
    if (result) {
        printf("Test 2 Passed: Found 'H' at position: %ld\n", result - test_str);
    } else {
        printf("Test 2 Failed: 'H' not found.\n");
    }

    // Test 3: Find a character at the end
    result = ft_memchr(test_str, '!', len);
    if (result) {
        printf("Test 3 Passed: Found '!' at position: %ld\n", result - test_str);
    } else {
        printf("Test 3 Failed: '!' not found.\n");
    }

    // Test 4: Find a character that does not exist
    result = ft_memchr(test_str, 'x', len);
    if (!result) {
        printf("Test 4 Passed: 'x' not found as expected.\n");
    } else {
        printf("Test 4 Failed: 'x' found at position: %ld\n", result - test_str);
    }

    // Test 5: Search an empty string
    const char *empty_str = "";
    result = ft_memchr(empty_str, 'a', 0);
    if (!result) {
        printf("Test 5 Passed: No character found in an empty string.\n");
    } else {
        printf("Test 5 Failed: Found character in an empty string.\n");
    }
	return(0);
}
*/
