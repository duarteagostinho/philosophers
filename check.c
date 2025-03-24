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

int check_4args(char *philos, char *die, char *eat, char *sleep)
{
	int	nr_of_philos;

	if (!ft_isdigit(philos) || !ft_isdigit(die) || !ft_isdigit(eat)
		|| !ft_isdigit(sleep))
	{
		printf("Invalid parameters\n");
		return (1);
	}
	nr_of_philos = ft_atoi(philos);
	if (!(nr_of_philos >= 1 && nr_of_philos <= 200))
	{
		printf("Invaldid number of philos\n");
		return (1);
	}
	return (0);
}

int check_5args(char *philos, char *die, char *eat, char *sleep, char *opt)
{
	int	nr_of_philos;

	nr_of_philos = 0;
	if (!ft_isdigit(philos) || !ft_isdigit(die) || !ft_isdigit(eat)
		|| !ft_isdigit(sleep) || !ft_isdigit(opt))
	{
		printf("Invalid parameters\n");
		return (1);
	}
	nr_of_philos = ft_atoi(philos);
	if (!(nr_of_philos > 0 && nr_of_philos <= 200))
	{
		printf("Invaldid number of philos\n");
		return (1);
	}
	return (0);
}
