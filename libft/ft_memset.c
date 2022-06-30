/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:24:48 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/11/29 00:11:29 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to write len bytes of value c to the string b
//returns a void

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s1;

	s1 = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		s1[i] = c;
		i++;
	}
	return (b);
}
