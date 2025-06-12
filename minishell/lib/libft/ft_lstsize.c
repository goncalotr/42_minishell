/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:44:56 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:11:41 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_lstsize
** 
** Prototype
** int ft_lstsize(t_list *lst);
** 
** Turn in files
** -
** 
** Parameters lst:
** The beginning of the list.
** 
** Return value
** The length of the list
** 
** External functs.
** None
** 
** Description
** Counts the number of nodes in a list.
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
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

void ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return;
	new->next = *lst;
	*lst = new;
}

#include <stdio.h>


void print_list(t_list *lst) {
    t_list *current = lst;
    while (current != NULL) {
        printf("Node content: %d\n", *(int *)current->content);
        current = current->next;
    }
}

int main() {
    t_list *head = NULL;

    int *value1 = malloc(sizeof(int)); *value1 = 42;
    t_list *node1 = ft_lstnew(value1);
    ft_lstadd_front(&head, node1);

    int *value2 = malloc(sizeof(int)); *value2 = 100;
    t_list *node2 = ft_lstnew(value2);
    ft_lstadd_front(&head, node2);

    int *value3 = malloc(sizeof(int)); *value3 = 200;
    t_list *node3 = ft_lstnew(value3);
    ft_lstadd_front(&head, node3);

    int size = ft_lstsize(head);
    printf("The size of the list is: %d\n", size);

    printf("Contents of the list:\n");
    print_list(head);

    t_list *current = head;
    while (current != NULL) {
        t_list *temp = current;
        current = current->next;
        free(temp->content);
        free(temp);
    }

    return 0;
}
*/
