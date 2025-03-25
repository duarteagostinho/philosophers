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

bool	check_args(char **av, bool optional)
{
	int	nr_of_philos;

	if (optional == true)
	{
		if (!ft_isdigit(av[5]))
		{
			printf("Invalid parameter\n");
			return (false);
		}
	}
	if (!ft_isdigit(av[1]) || !ft_isdigit(av[2]) || !ft_isdigit(av[3])
		|| !ft_isdigit(av[4]))
	{
		printf("Invalid parameters\n");
		return (false);
	}
	nr_of_philos = ft_atoi(av[1]);
	if (!(nr_of_philos >= 1 && nr_of_philos <= 200))
	{
		printf("Invaldid number of philos\n");
		return (false);
	}
	return (true);
}

bool	checker(int ac, char **av)
{
	if (ac == 4)
		return (check_args(av, false));
	else if (ac == 5)
		return (check_args(av, true));
	else
	{
		printf("Invalid number of arguments\n");
		return (false);
	}
}