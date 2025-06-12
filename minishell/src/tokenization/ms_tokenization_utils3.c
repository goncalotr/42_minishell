/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:37:29 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/02 16:58:37 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_append_char(char *str, char c)
{
	int		len;
	char	*new_str;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = malloc (len + 2);
	if (!new_str)
		return (NULL);
	if (str)
		ft_strlcpy(new_str, str, len + 2);
	else
		new_str[0] = '\0';
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free (str);
	return new_str;
}

char	*ms_str_append(char *str1, char *str2)
{
	int		len;
	char	*new_str;

	len = 0;
	if (str1)
		len = ft_strlen(str1);
	new_str = malloc(len + ft_strlen(str2) + 1);
	if (!new_str)
		return (NULL);
	if (str1)
		ft_strlcpy(new_str, str1, len + ft_strlen(str2) + 1);
	else
		new_str[0] = '\0';
	ft_strlcat(new_str, str2, len + ft_strlen(str2) + 1);
	free(str1);
	free(str2);
	return (new_str);
}

char	*ms_strndup(char *str, size_t n)
{
	char 		*dest;
	size_t		i;
	
	i = 0;
	if (!str)
		return (NULL);
	dest = malloc(n + 1);
	if (!dest)
		return (NULL);
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

bool	ms_ismetachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

bool	ms_isspace(char c)
{
	if (c == 32 || (c >= 7 && c <= 13))
		return (true);
	else
		return (false);
}