/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:12:37 by jpedro-f          #+#    #+#             */
/*   Updated: 2024/11/15 17:12:39 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_found_newline(t_list_gnl *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str[i] && i < BUFFER_SIZE)
		{
			if (list->str[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

t_list_gnl	*ft_find_last_node(t_list_gnl *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_copy_str(t_list_gnl *list, char *new_str)
{
	int	i;
	int	x;

	if (list == NULL)
		return ;
	x = 0;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
			{
				new_str[x++] = '\n';
				new_str[x] = '\0';
				return ;
			}
			new_str[x++] = list->str[i++];
		}
		list = list->next;
	}
	new_str[x] = '\0';
}

int	ft_len_list(t_list_gnl *list)
{
	int	len;
	int	i;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
			{
				++len;
				return (len);
			}
			++len;
			++i;
		}
		list = list->next;
	}
	return (len);
}

void	ft_dealloc(t_list_gnl **list, t_list_gnl *clean_node, char *buf)
{
	t_list_gnl	*temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->str);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (!clean_node || !buf)
		return ;
	if (clean_node->str[0])
		*list = clean_node;
	else
	{
		free(clean_node);
		free(buf);
	}
}
