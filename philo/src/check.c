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

#include "../philo.h"

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((av[i][j] < 48 || av[i][j] > 57))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	checker(int ac, char **av)
{
	if (ac == 5 || ac == 6)
		return (check_args(av));
	else
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
}
