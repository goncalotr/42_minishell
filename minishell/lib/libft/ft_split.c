/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:00:47 by goteixei          #+#    #+#             */
/*   Updated: 2025/02/24 14:42:17 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_split
** 
** Prototype
** char **ft_split(char const *s, char c);
** 
** Turn in files
** -
** 
** Parameters
** s: The string to be split.
** c: The delimiter character.
** 
** Return value
** The array of new strings resulting from the split.
** NULL if the allocation fails.
** External functs. malloc, free
** 
** Description
** Allocates (with malloc(3)) and returns an array
** of strings obtained by splitting ’s’ using the
** character ’c’ as a delimiter. The array must end
** with a NULL pointer.
*/

#include "libft.h"

static char	**ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free (strs);
	return (NULL);
}

size_t	count_words(char const *str, char c)
{
	size_t	words;
	int		i;
	int		in_word;

	i = 0;
	words = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != c && in_word == 0)
		{
			words++;
			in_word = 1;
		}
		if (str[i] == c)
		{
			in_word = 0;
		}
		i++;
	}
	return (words);
}

size_t	next_word_pos(char const *s, char c, size_t i_pos, int mode)
{
	size_t	next_word_pos;

	next_word_pos = i_pos;
	if (mode == 1)
	{
		while (s[next_word_pos] == c && s[next_word_pos])
		{
			next_word_pos++;
		}
		return (next_word_pos);
	}
	else
	{
		while (s[next_word_pos] != c && s[next_word_pos])
		{
			next_word_pos++;
		}
		return (next_word_pos);
	}
}

char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		str_i;

	str_i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
	{
		if (str[str_i] == '\'')
		{
			str_i++;
		}
		word[str_i++] = str[start++];
	}
	word[str_i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result_lst;
	size_t	result_i1;
	size_t	s_i;
	size_t	next_word;

	result_i1 = 0;
	s_i = 0;
	next_word = 0;
	if (s == NULL)
		return (NULL);
	result_lst = (char **)malloc((count_words(s, c) + 1) * (sizeof(char *)));
	if (result_lst == NULL)
		return (NULL);
	while (result_i1 < count_words (s, c))
	{
		s_i = next_word_pos(s, c, s_i, 1);
		next_word = next_word_pos(s, c, s_i, 2);
		result_lst[result_i1] = word_dup(s, s_i, next_word);
		if (!result_lst[result_i1])
			return (ft_free(result_lst, result_i1), NULL);
		result_i1++;
		s_i = next_word;
	}
	result_lst[result_i1] = NULL;
	return (result_lst);
}

/*
size_t	ft_split_count(const char *s, char c)
{
	size_t	i;
	size_t	prev;
	size_t	next;
	size_t	size;
	size_t	counter;

	i = 0;
	prev = i;
	next = i;
	counter = 0;
	while (1)
	{
		if (s[i] == c || s[i] == '\0')
			next = i;
		size = next - prev;
		if (size > 1 || (size == 1 && s[i - 1] != c))
			counter++;
		if (s[i] == '\0')
			break ;
		prev = next;
		i++;
	}
	return (counter);
}
*/

/*
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void print_string_array(char **array)
{
    int i = 0;

    while (array[i] != NULL)
    {
        printf("String %d: %s\n", i, array[i]);
        i++;
    }
}

void test_ft_split(const char *input, char delimiter, int expected_count)
{
    char **result = ft_split(input, delimiter);
    int i;

    printf("Expected %d strings in split result:\n", expected_count);
    for (i = 0; i < expected_count; i++)
    {
        if (result[i] != NULL)
            printf("result[%d]: %s\n", i, result[i]);
        else
            printf("result[%d]: NULL (unexpected)\n", i);
    }

    if (result[expected_count] == NULL)
        printf("result[%d]: NULL (correct, end of array)\n", expected_count);
    else
        printf("result[%d]: %s (unexpected, should be NULL)\n", 
		expected_count, result[expected_count]);

    printf("\nTesting access beyond NULL terminator:\n");
    for (i = expected_count + 1; i < expected_count + 3; i++)
    {
        printf("Attempting to access result[%d]...\n", i);
        printf("result[%d]: %p (pointer should be inaccessible)\n",
		i, (void*)result[i]);
    }

    for (i = 0; i < expected_count && result[i] != NULL; i++)
    {
        free(result[i]);
    }
    free(result);
}

int main(void)
{
	char *test_str = "b11111b222222b3b4b5555b";
	char test_char = 'b';
	printf("Test String: %s\n", test_str);
	printf("Splits: %ld \n", count_words(test_str, test_char));

	printf("Start\n");
	int i = 0;
	while (i < ft_strlen(test_str))
	{
		printf("P: %ld ", next_word_pos(test_str, test_char, i, 1));
		i++;
	}
	printf("\n");

	printf("End\n");
	i = 0;
	while (i < ft_strlen(test_str))
	{
		printf("P: %ld ", next_word_pos(test_str, test_char, i, 2));
		i++;
	}
	printf("\n");

	print_string_array(ft_split(test_str, test_char));

	printf("\n\n\n");
	printf("Number of words: %ld\n", count_words("hello!", ' '));
    test_ft_split("hello!", ' ', 1);
	printf("\n\n\n");
	printf("Number of words: %ld\n", count_words("hello!\n12345", '\n'));
    test_ft_split("hello!\n12345", '\n', 2);
	printf("\n\n\n");
	printf("Number of words: %ld\n", count_words("hello!\0a12345", '\0'));
    test_ft_split("hello!\0a12345", '\0', 2);
	printf("\n\n\n");
	printf("Number of words: %ld\n", count_words("hello!\0a12345", '3'));
    test_ft_split("hello!\0a12345", '\0', 2);
	printf("\n\n\n");
	printf("Number of words: %ld\n", count_words("hello!-a ", ' '));
    test_ft_split("hello!-a ", ' ', 1);
	printf("\n\n\n");
	return (0);
}
*/
