/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:16:53 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/01 14:11:28 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function's goal is to write 1 char on the file descriptor in parameter

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
