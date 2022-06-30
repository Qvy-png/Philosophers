/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:53:09 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/05/24 17:53:28 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **twoD)
{
	int	i;

	i = 0;
	while (twoD && twoD[i] != NULL)
	{
		free(twoD[i]);
		i++;
	}
	if (twoD)
		free(twoD);
}