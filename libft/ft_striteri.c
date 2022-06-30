/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 09:28:54 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/01 14:17:53 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to apply a function given in parameters, onto each 
//index of the given string

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;
	int	len;

	if (!s)
		return ;
	i = 0;
	len = ft_strlen(s);
	if (!f || !s)
		return ;
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}
