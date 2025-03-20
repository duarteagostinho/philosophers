/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:01:27 by duandrad          #+#    #+#             */
/*   Updated: 2025/03/19 20:01:56 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_philo(int philos, int die, int eat, int sleep)
{
	philo()->philosophers = philos;
	philo()->forks = philo()->philosophers;
	philo()->die_time = die;
	philo()->eat_time = eat;
	philo()->sleep_time = sleep;
}

int main(int ac, char **av)
{
  /*av[1] = nr_philos, av[2] = timeto_die, av[3] = timeto_eat, av[4] timeto_sleep*/ 
  if(ac > 1)
  {
	init_philo(ft_atoi(av[1]), ft_atoi(av[2]), ft_atoi(av[3]), ft_atoi(av[4]));
  }
  else
    ft_putstr("Invalid number of arguments\n");
}
