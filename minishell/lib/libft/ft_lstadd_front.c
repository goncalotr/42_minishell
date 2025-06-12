/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:22:37 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:13:51 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_lstadd_front
** 
** Prototype
** void ft_lstadd_front(t_list **lst, t_list *new);
** 
** Turn in files
** -
** 
** Parameters
** lst: The address of a pointer to the first link of a list.
** new: The address of a pointer to the node to be
** added to the list.
** 
** Return value
** None
** 
** External functs.
** None
** 
** Description
** Adds the node ’new’ at the beginning of the list.
*/

#include "libft.h"

/**
 * ft_lstadd_front - Adds a node at the beginning of the list.
 * @lst: The address of a pointer to the first link of a list.
 * @new: The address of a pointer to the node to be added to the list.
 */

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
t_list *ft_lstnew(void *content)
{
	t_list *new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return new_node;
}
*/

/*
#include <stdio.h>

int main() {
    t_list *head = NULL;

    int *value1 = malloc(sizeof(int));
    *value1 = 42;
    t_list *node1 = ft_lstnew(value1);

    ft_lstadd_front(&head, node1);

    int *value2 = malloc(sizeof(int));
    *value2 = 100;
    t_list *node2 = ft_lstnew(value2);

    ft_lstadd_front(&head, node2);

    t_list *current = head;
    while (current != NULL) {
        printf("Node content: %d\n", *(int *)current->content);
        current = current->next;
    }

	free(node1);
	free(node2);
	free(head);

	current = head;
    while (current != NULL) {
        t_list *temp = current;
        current = current->next;
        free(temp->content);
        free(temp);
    }

    return 0;
}
*/
