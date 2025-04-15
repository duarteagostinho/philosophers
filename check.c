/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:48:51 by duandrad          #+#    #+#             */
/*   Updated: 2025/03/24 16:52:59 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av, bool optional)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	write(1, "passei 0", 9);
	if (!av)
		return (1);
	write(1, "passei 1", 9);
	if (optional == true)
		while (av[5][++j])
			if (!ft_isaldigit(av[5][j]))
				return (1);
	write(1, "passei 2", 9);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	checker(int ac, char **av)
{
	if (ac == 4)
		return (check_args(av, false));
	else if (ac == 5)
		return (check_args(av, true));
	else
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
}
