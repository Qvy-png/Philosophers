/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:34:30 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/01 10:20:57 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)hay);
	while (hay[i] != '\0' && i < len)
	{
		j = 0;
		while (hay[i + j] != '\0' && (i + j < len) && needle[j] != '\0'
			&& hay[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)hay + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
