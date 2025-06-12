/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:27:02 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 15:08:20 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_strjoin
** 
** Prototype
** char *ft_strjoin(char const *s1, char const *s2);
** 
** Turn in files
** -
** 
** Parameters
** s1: The prefix string.
** s2: The suffix string.
** 
** Return value
** The new string.
** NULL if the allocation fails.
** 
** External functs.
** malloc
** 
** Description
** Allocates (with malloc(3)) and returns a new
** string, which is t
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_str1;
	size_t	len_str2;
	size_t	i;
	char	*joined_str;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_str1 = ft_strlen(s1);
	len_str2 = ft_strlen(s2);
	joined_str = (char *)malloc((len_str1 + len_str2 + 1) * sizeof(char));
	if (joined_str == NULL)
		return (NULL);
	while (i < len_str1)
	{
		joined_str[i] = s1[i];
		i++;
	}
	while (i < (len_str1 + len_str2))
	{
		joined_str[i] = s2[i - len_str1];
		i++;
	}
	joined_str[i] = '\0';
	return (joined_str);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *s1, *s2, *result;

    // Normal case
    s1 = "Hello, ";
    s2 = "World!";
    result = ft_strjoin(s1, s2);
    printf("Test 1: %s\n", (result != NULL && strcmp(result, 
	"Hello, World!") == 0) ? "Passed" : "Failed");
    free(result);

    // Empty prefix
    s1 = "";
    s2 = "World!";
    result = ft_strjoin(s1, s2);
    printf("Test 2: %s\n", (result != NULL && strcmp(result, "World!") 
	== 0) ? "Passed" : "Failed");
    free(result);

    // Empty suffix
    s1 = "Hello, ";
    s2 = "";
    result = ft_strjoin(s1, s2);
    printf("Test 3: %s\n", (result != NULL && strcmp(result, "Hello, ") 
	== 0) ? "Passed" : "Failed");
    free(result);

    // Both strings empty
    s1 = "";
    s2 = "";
    result = ft_strjoin(s1, s2);
    printf("Test 4: %s\n", (result != NULL && strcmp(result, "") 
	== 0) ? "Passed" : "Failed");
    free(result);

    s1 = "adsadsd da123";
    s2 = "456asd as as f";
    result = ft_strjoin(s1, s2);
    printf("Test 5: %s\n", result);
    free(result);
    return 0;
}
*/
