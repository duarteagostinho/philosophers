/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:25:12 by gloryboydud       #+#    #+#             */
/*   Updated: 2025/07/21 20:11:01 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(int ac, char **av, t_data *data)
{
	data->philo_num = atoi(av[1]);
	data->death_time = atoi(av[2]);
	data->eat_time = atoi(av[3]);
	data->sleep_time = atoi(av[4]);
	if (ac == 6)
		data->meals_nb = atoi(av[5]);
	else
		data->meals_nb = -1;
	if (data->philo_num <= 0 || data->philo_num > 200 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0)
		return (1);
	data->dead = 0;
	data->start_time = get_time();
	data->finished = 0;
	data->all_finished = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	alloc_structs(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->tid)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (1);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->philo_num - 1];
	i = 1;
	while (i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].last_meal = get_time();
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eat_cont = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

int	init_all(int ac, char **av, t_data *data)
{
	if (init_data(ac, av, data))
	{
		ft_putstr("Error: Init data\n");
		return (1);
	}
	if (alloc_structs(data))
	{
		ft_putstr("Error: Allocating structs\n");
		return (1);
	}
	if (init_forks(data))
	{
		ft_putstr("Error: Init forks\n");
		return (1);
	}
	init_philos(data);
	return (0);
}
