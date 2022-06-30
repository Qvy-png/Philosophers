/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:07:33 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/11/26 11:50:12 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to detect the first occurence of a char in a string
//returns a pointer to the located char, or NULL if none is found

char	*ft_strchr(const char *s, int c)
{
	int				string_length;
	int				i;

	i = 0;
	string_length = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[string_length]);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
