/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:51:10 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/01 13:59:21 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to n zeroed bytes to te string s
//returns nothing

void	ft_bzero(void *s, size_t n)
{
	char	*s1;

	s1 = (char *)s;
	if (n > 0)
		ft_memset(s1, 0, n);
}
