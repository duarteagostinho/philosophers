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

#include "../philo.h"

void	one_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(data->death_time);
	printf("%u 1 has died\n", data->death_time);
	ft_exit(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (checker(ac, av))
	{
		ft_putstr("Checker Error\n");
		return (1);
	}
	if (init_all(ac, av, &data))
	{
		ft_putstr("Init All Error\n");
		return (1);
	}
	if (data.philo_num == 1)
	{
		one_philo(&data);
		return (0);
	}
	if (thread_init(&data))
	{
		ft_putstr("Thread Init Error\n");
		return (1);
	}
	ft_exit(&data);
	return (0);
}
