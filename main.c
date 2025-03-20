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

int main(int ac, char **av)
{
  int j;
  int i;

  i = -1;
  j = 1;
  /*av[1] = nr_philos, av[2] = timeto_die, av[3] = timeto_eat, av[3] timeto_sleep*/ 
  if(ac > 1)
  {
    philo()->philosophers = ft_atoi(av[1]);
    philo()->forks = philo()->philosophers;
    printf("nr of philos = %d\n", philo()->philosophers);
  }
  else
    ft_putstr("Invalid number of arguments\n");
}
