/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:01:27 by duandrad          #+#    #+#             */
/*   Updated: 2025/03/24 17:15:08 by gloryboydud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	checker(int ac, char **av)
{
	bool	check;

	check = false;
	if(ac == 4 || ac == 5)
	{
		if (ac == 4)
			check += check_4args(av[1], av[2], av[3], av[4]);
		if (ac == 5)
			check += check_5args(av[1], av[2], av[3], av[4], av[5]);
		if (!check)
			return (false);
	}
	else
		printf("Invalid number of arguments\n");
	return (check);
}
int main(int ac, char **av)
{
	bool	check;

	if (checker(ac, av) == true)
	{
		if (ac == 4)
		if (ac == 5)
	}
	else
		ft_putstr("Invalid number of arguments\n");
}
