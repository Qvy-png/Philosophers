/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:24:42 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/07/16 18:21:08 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	helper(void)
{
	printf("WRONG USAGE !\n");
	printf("\033[0;31mUsage: \033[0m./philo (int)[NUM_OF_PHILO] ");
	printf("(int)[TIME_TO_DIE] (int)[TIME_TO_EAT] (int)[TIME_TO_SLEEP] ");
	printf("optionnal->(int)[NUM_OF_MEALS]\n");
	
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	verif(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') &&
				argv[i][j] >= 32 && argv[i][j] < 127)
				return (1);
			if (ft_atoi(argv[i]) > 2147483647 || ft_strlen(argv[i]) > 12)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philostruct	*p;

	p = malloc(sizeof(t_philostruct));
	if (!p)
		return (0);
	if (argc == 5 || argc == 6)
	{
		if (verif(argv) == 1)
			return (helper(), free(p), 0);
		init(p, argv);
		philo_creator(p);
		philo_launcher(p);
		demallocage(p);
	}
	free(p);
	return (0);
}
