/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:19:12 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/02 09:29:14 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to apply a function to a whole list, create a new
//list with results from this work and use del to destroy elemets if needed

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list1;
	t_list	*list2;

	list1 = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		list2 = ft_lstnew((*f)(lst->content));
		if (!list2)
		{
			while (list1)
			{
				list2 = list1->next;
				(*del)(list1->content);
				free(list1);
				list1 = list2;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&list1, list2);
		lst = lst->next;
	}
	return (list1);
}
