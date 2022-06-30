/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:06:54 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/01 14:00:30 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to malloc but fill the space with zeros
//returns the allocated string

void	*ft_calloc(size_t i, size_t j)
{
	char	*s1;

	s1 = (char *)malloc(sizeof(char) * (j * i));
	if (s1 == NULL)
		return (NULL);
	ft_bzero(s1, j * i);
	return (s1);
}
