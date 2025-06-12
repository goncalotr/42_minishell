/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:12:09 by goteixei          #+#    #+#             */
/*   Updated: 2024/12/22 19:15:07 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_bzero(void *s, size_t len)
{
	char	*p;

	p = (char *)s;
	while (len > 0)
	{
		p[len - 1] = '\0';
		len--;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	cc;

	cc = (char) c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == cc)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, const char *s2)
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
		return (free(s1), NULL);
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
	return (free(s1), joined_str);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
