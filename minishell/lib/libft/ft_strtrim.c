/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:44:56 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:08:53 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_strtrim
** 
** Prototype
** char *ft_strtrim(char const *s1, char const *set);
** 
** Turn in files
** -
** 
** Parameters
** s1: The string to be trimmed.
** set: The reference set of characters to trim.
** 
** Return value
** The trimmed string.
** NULL if the allocation fails.
** 
** External functs.
** malloc
** 
** Description
** Allocates (with malloc(3)) and returns a copy of
** ’s1’ with the characters specified in ’set’ removed
** from the beginning and the end of the string.
*/

#include "libft.h"

int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	start = 0;
	while ((s1[i] != '\0') && (ft_char_in_set(s1[start], set) == 1))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_char_in_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *s1, *set, *result;

    // Normal case
    s1 = "   Hello, World!   ";
    set = " ";
    result = ft_strtrim(s1, set);
    printf("Test 1: '%s'\n", (result != NULL &&
	strcmp(result, "Hello, World!") == 0) ? "Passed" : "Failed");
    free(result);

    // Trimming with multiple characters
    s1 = "---Hello, World!---";
    set = "-";
    result = ft_strtrim(s1, set);
    printf("Test 2: '%s'\n", (result != NULL &&
	strcmp(result, "Hello, World!") == 0) ? "Passed" : "Failed");
    free(result);

    // Only trimming characters from the start
    s1 = "   Hello, World!";
    set = " ";
    result = ft_strtrim(s1, set);
    printf("Test 3: '%s'\n", (result != NULL &&
	strcmp(result, "Hello, World!") == 0) ? "Passed" : "Failed");
    free(result);

    // Only trimming characters from the end
    s1 = "Hello, World!   ";
    set = " ";
    result = ft_strtrim(s1, set);
    printf("Test 4: '%s'\n", (result != NULL &&
	strcmp(result, "Hello, World!") == 0) ? "Passed" : "Failed");
    free(result);

    // No characters to trim
    s1 = "Hello, World!";
    set = "xyz";
    result = ft_strtrim(s1, set);
    printf("Test 5: '%s'\n", (result != NULL &&
	strcmp(result, "Hello, World!") == 0) ? "Passed" : "Failed");
    free(result);

    // Trimming an empty string
    s1 = "";
    set = " ";
    result = ft_strtrim(s1, set);
    printf("Test 6: '%s'\n", (result != NULL &&
	strcmp(result, "") == 0) ? "Passed" : "Failed");
    free(result);

    // Trimming with NULL input
    result = ft_strtrim(NULL, set);
    printf("Test 7: %s\n", result == NULL ? "Passed" : "Failed");

    return 0;
}
*/