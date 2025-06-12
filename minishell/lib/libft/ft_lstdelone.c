/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:19:49 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/02 21:53:16 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_lstdelone
** 
** Prototype
** void ft_lstdelone(t_list *lst, void (*del)(void*));
** 
** Turn in files
** -
** 
** Parameters
** lst: The node to free.
** del: The address of the function used to delete the content.
** 
** Return value
** None
** 
** External functs.
** free
** 
** Description
** Takes as a parameter a node and frees the memory of
** the node’s content using the function ’del’ given
** as a parameter and free the node. The memory of
** ’next’ must not be freed.
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}

/*
#include <stdio.h>
#include <stdlib.h>

void del_content(void *content) {
    free(content);
}

t_list *ft_lstnew(void *content) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (new_node == NULL) return NULL;
    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}

int main() {
    t_list *node = ft_lstnew(malloc(sizeof(int)));
    *(int *)node->content = 42;

    printf("Node content before deletion: %d\n", *(int *)node->content);
    
    ft_lstdelone(node, del_content);

    return 0;
}
*/
