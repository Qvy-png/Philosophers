/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:46:15 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/01 14:18:21 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to concatenate 2 strings together 

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	int		i;
	int		j;
	int		len1;
	int		len2;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	r = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (r == NULL)
		return (NULL);
	while (i < len1)
	{
		r[i] = s1[i];
		i++;
	}
	while (j < len2)
		r[i++] = s2[j++];
	r[i] = '\0';
	return (r);
}
