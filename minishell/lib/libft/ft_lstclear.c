/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:26:38 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/09 08:47:07 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_lstclear
** 
** Prototype
** void ft_lstclear(t_list **lst, void (*del)(void*));
** 
** Turn in files
** -
** 
** Parameters
** lst: The address of a pointer to a node.
** del: The address of the function used to delete the content of the node.
** 
** Return value
** None
** 
** External functs.
** free
** 
** Description
** Deletes and frees the given node and every
** successor of that node, using the function ’del’
** and free(3).
** Finally, the pointer to the list must be set to
** NULL.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next_node;

	current = *lst;
	if (lst == NULL || del == NULL)
		return ;
	while (current != NULL)
	{
		next_node = current->next;
		del(current->content);
		free(current);
		current = next_node;
	}
	*lst = NULL;
}

/*
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


#include <stdio.h>
#include <stdlib.h>

int main() {
    t_list *head = NULL;

    for (int i = 0; i < 3; i++) {
        int *value = malloc(sizeof(int));
        *value = (i + 1) * 10;
        t_list *new_node = ft_lstnew(value);
        new_node->next = head;
        head = new_node;
    }

    ft_lstclear(&head, del_content);

    if (head == NULL) {
        printf("List cleared successfully.\n");
    } else {
        printf("List not cleared.\n");
    }

    return 0;
}
*/
