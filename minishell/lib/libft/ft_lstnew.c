/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:58:58 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/02 22:01:02 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_lstnew
** 
** Prototype
** t_list *ft_lstnew(void *content);
** 
** Turn in files
** -
** 
** Parameters content:
** The content to create the node with.
** 
** Return value
** The new node
** 
** External functs.
** malloc
** 
** Description
** Allocates (with malloc(3)) and returns a new node.
** The member variable ’content’ is initialized with
** the value of the parameter ’content’. The variable
** ’next’ is initialized to NULL.
*/

#include "libft.h"

/**
 * ft_lstnew - Allocates and returns a new node.
 * @content: The content to create the node with.
 *
 * Return: The new node, or NULL if allocation fails.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/*
#include <stdio.h>

int main()
{
    int value = 42;
    t_list *node = ft_lstnew(&value);

    if (node != NULL)
    {
        printf("Node created with content: %d\n", *(int *)node->content);
        free(node); // Don't forget to free allocated memory
    }
    else
    {
        printf("Failed to create node.\n");
    }

    return 0;
}
*/