/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:13:49 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/01 13:38:32 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to allocate and return a string copied from
//the index start from the source string given in parameter, to either the end 
//of the string, or the end of the given length in parameter.
//returns a char pointer if success, or a NULL if malloc fails

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;
	size_t	j;
	size_t	lenbis;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	lenbis = ft_strlen(s + start);
	if (lenbis < len)
		len = lenbis;
	s1 = (char *)malloc(sizeof(*s) * (len + 1));
	if (s1 == NULL)
		return (NULL);
	while (i < start)
		i++;
	while (s[i] && j < len)
		s1[j++] = s[i++];
	s1[j] = '\0';
	return (s1);
}
