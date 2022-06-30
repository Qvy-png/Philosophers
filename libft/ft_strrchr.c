/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:39:21 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/11/26 11:51:54 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//this function's goal is to locate the last occurence of c in a given string
//returns a pointer to the located characterm or NULL if none is found

char	*ft_strrchr(const char *s, int c)
{
	int	string_length;
	int	i;

	string_length = ft_strlen(s);
	i = string_length;
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
