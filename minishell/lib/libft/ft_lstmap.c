/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:36:03 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/09 09:03:17 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_lstmap
** 
** Prototype
** t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
** 
** Turn in files
** -
** 
** Parameters
** lst: The address of a pointer to a node.
** f: The address of the function used to iterate on the list.
** del: The address of the function used to delete
** the content of a node if needed.
** 
** Return value
** The new list.
** NULL if the allocation fails.
** 
** External functs.
** malloc, free
** 
** Description
** Iterates the list ’lst’ and applies the function
** ’f’ on the content of each node. Creates a new
** list resulting of the successive applications of
** the function ’f’. The ’del’ function is used to
** delete the content of a node if needed.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		if (new_content == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/*
#include <stdio.h>
#include <stdlib.h>

void *double_content(void *content) {
    int *new_content = malloc(sizeof(int));
    *new_content = (*(int *)content) * 2;
    return new_content;
}

void delete_content(void *content) {
    free(content);
}

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return;

	t_list *current = *lst;
	t_list *next_node;

	while (current != NULL)
	{
		next_node = current->next;
		del(current->content);
		free(current);
		current = next_node;
	}
	*lst = NULL;
}
void ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		t_list *last_node = *lst;
		while (last_node->next != NULL)
		{
			last_node = last_node->next;
		}
		last_node->next = new;
	}
}

t_list *ft_lstnew(void *content)
{
	t_list *new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return new_node;
}

void print_list(t_list *lst) {
    while (lst != NULL) {
        printf("Node content: %d\n", *(int *)lst->content);
        lst = lst->next;
    }
}

int main() {
    t_list *head = NULL;

    for (int i = 1; i <= 3; i++) {
        int *value = malloc(sizeof(int));
        *value = i * 10;
        t_list *node = ft_lstnew(value);
        ft_lstadd_back(&head, node);
    }

    t_list *mapped_list = ft_lstmap(head, double_content, delete_content);

    printf("Original list:\n");
    print_list(head);

    printf("\nMapped list (content doubled):\n");
    print_list(mapped_list);

    ft_lstclear(&head, delete_content);
    ft_lstclear(&mapped_list, delete_content);

    return 0;
}
*/
