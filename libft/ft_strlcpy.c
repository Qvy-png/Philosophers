/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:00:00 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/01 14:19:36 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to copy a string into another
//returns the size of the dst string, in size_t 

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((char)dst[i] != '\0')
		i++;
	while ((char)src[j] != '\0' && j + 1 < dstsize)
	{
		dst[j] = (char)src[j];
		j++;
	}
	if (j < dstsize)
		dst[j] = '\0';
	return (ft_strlen((char *)src));
}
