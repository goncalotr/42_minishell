/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:36:39 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:07:56 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        strdup, strndup, strdupa, strndupa - duplicate a string
** 
** SYNOPSIS
**        #include <string.h>
** 
**        char *strdup(const char *s);
** 
**        char *strndup(const char *s, size_t n);
**        char *strdupa(const char *s);
**        char *strndupa(const char *s, size_t n);
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	str_len;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/*
#include <stdio.h>

int main()
{
    char *s = "Hello, World!";
    char *substr;

    substr = ft_substr(s, 7, 5);
    printf("Test 1: %s\n", (substr != NULL &&
	strcmp(substr, "World") == 0) ? "Passed" : "Failed");
    free(substr);

    substr = ft_substr(s, 20, 5);
    printf("Test 2: %s\n", (substr != NULL &&
	strcmp(substr, "") == 0) ? "Passed" : "Failed");
    free(substr);

    substr = ft_substr(s, 7, 10);
    printf("Test 3: %s\n", (substr != NULL &&
	strcmp(substr, "World!") == 0) ? "Passed" : "Failed");
    free(substr);

    substr = ft_substr(s, 7, 0);
    printf("Test 4: %s\n", (substr != NULL &&
	strcmp(substr, "") == 0) ? "Passed" : "Failed");
    free(substr);

    substr = ft_substr(s, 0, strlen(s));
    printf("Test 5: %s\n", (substr != NULL &&
	strcmp(substr, s) == 0) ? "Passed" : "Failed");
    free(substr);

    return 0;
}
*/