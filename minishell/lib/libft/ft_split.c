/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:02:51 by jpedro-f          #+#    #+#             */
/*   Updated: 2024/10/27 18:02:52 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// Splits a string into an array of strings
/// s	Pointer to the string
/// c	Separator
/// return		SUCCESSS(Pointer to the array of strings)
/// return		FAILURE(0)

static int	ft_substrings(const char *s, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (*s != c && in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		else if (*s == c)
			in_substring = 0;
		s++;
	}
	return (count);
}

static char	*ft_copy(char const *start, char const *end)
{
	int		len;
	char	*substring;
	int		i;

	i = 0;
	len = end - start;
	substring = (char *) malloc(sizeof(char) * (len + 1));
	if (substring == NULL)
		return (NULL);
	while (i < len)
	{
		substring[i] = start[i];
		i++;
	}
	substring[len] = '\0';
	return (substring);
}

static char	**ft_free(char **array, int i)
{
	while (i > 0)
	{
		free(array[--i]);
	}
	free(array);
	return (NULL);
}

static char	**ft_allocate(char const *s, char c)
{
	char		**array;

	if (s == NULL)
		return (NULL);
	array = (char **) malloc(sizeof(char *) * (ft_substrings(s, c) + 1));
	if (array == NULL)
		return (NULL);
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char		**array;
	char const	*start;
	int			i;

	i = 0;
	array = ft_allocate(s, c);
	if (array == NULL)
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		start = s;
		while (*s != '\0' && *s != c)
			s++;
		if (s > start)
		{
			array[i] = ft_copy(start, s);
			if (array[i] == NULL)
				return (ft_free(array, i));
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}

// int	main(void)
// {
// 	char	*s = "lorem ipsum dolor sit";
// 	char	c = ' ';
// 	char	**array;
// 	int		i = 0;
// 	int		x;
//
// 	array = ft_split(s, c);
// 	while (array[i] != NULL)
// 	{
// 		x = 0;
// 		while (array[i][x] != '\0')
// 		{
// 			printf("%c", array[i][x]);
// 			x++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// 	return (0);
// }
