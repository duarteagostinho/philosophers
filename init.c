/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:25:12 by gloryboydud       #+#    #+#             */
/*   Updated: 2025/04/17 15:14:16 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int ac, char **av, t_data *data)
{
	data->philo_num = atoi(av[1]);
	data->death_time = atoi(av[2]);
	data->eat_time = atoi(av[3]);
	data->sleep_time = atoi(av[4]);
	data->meals_nb = -1;
	if (ac == 6)
		data->meals_nb = atoi(av[5]);
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (true);
}

int	alloc_structs(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->tid)
		return (false);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (false);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (false);
	return (true);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->philo_num - 1];
	i = 1;
	while (i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (true);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_cont = 0;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
	return (true);
}

int	init_all(int ac, char **av, t_data *data)
{
	if (!init_data(ac, av, data))
	{
		ft_putstr("Error: Init data\n");
		return (1);
	}
	if (!alloc_structs(data))
	{
		ft_putstr("Error: Allocating structs\n");
		return (1);
	}
	if (!init_forks(data))
	{
		ft_putstr("Error: Init forks\n");
		return (1);
	}
	if (!init_philos(data))
	{
		ft_putstr("Error: Init philos\n");
		return (1);
	}
	return (0);
}
