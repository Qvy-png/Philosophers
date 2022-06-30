/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:09:18 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/01 14:15:17 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This program's goal is to split a given string into words and write them in a
//tab, while allocating properly its memory
//returns a 2d char tab

int	ft_is_c(char index, char c)
{
	if (index == c)
	{
		return (0);
	}
	return (1);
}

int	ft_str_word(char const *s, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_is_c(s[i], c) == 0)
			i++;
		if (s[i] && ft_is_c(s[i], c) == 1)
		{
			word++;
			while (s[i] && ft_is_c(s[i], c) == 1)
				i++;
		}
	}
	return (word);
}

char	*ft_mallocage(char const *s, char c)
{
	char	*tab;
	int		i;

	i = 0;
	while (s[i] && ft_is_c(s[i], c) == 1)
		i++;
	tab = (char *)malloc(sizeof(char) * (i + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s[i] && ft_is_c(s[i], c) == 1)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**string;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = ft_str_word(s, c);
	j = 0;
	string = (char **)malloc(sizeof(char *) * (i + 1));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (s[j])
	{
		while (s[j] && ft_is_c(s[j], c) == 0)
			j++;
		if (s[j] && ft_is_c(s[j], c) == 1)
		{
			string[i++] = ft_mallocage((s + j), c);
			while (s[j] && ft_is_c(s[j], c) == 1)
				j++;
		}
	}
	string[i] = NULL;
	return (string);
}
