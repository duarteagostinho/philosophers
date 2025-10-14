/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mods.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:04:41 by duandrad          #+#    #+#             */
/*   Updated: 2025/10/13 15:45:47 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	help_monitor(t_data	*data)
{
	int		i;

	pthread_mutex_lock(&data->lock);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->lock);
		return ;
	}
	pthread_mutex_unlock(&data->lock);
	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		if ((get_time() - data->philos[i].last_meal)
			>= data->philos[i].time_to_die)
		{
			print_message("died", &data->philos[i]);
			pthread_mutex_lock(&data->lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->lock);
			pthread_mutex_unlock(&data->philos[i].lock);
			return ;
		}
		pthread_mutex_unlock(&data->philos[i].lock);
	}
}

void	*monitor(void *pt)
{
	t_data	*data;

	data = (t_data *)pt;
	while (1)
	{
		help_monitor(data);
		pthread_mutex_lock(&data->lock);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		if (data->meals_nb != -1 && data->finished >= data->philo_num)
		{
			data->dead = 1;
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->lock);
		ft_usleep(1);
	}
	return (NULL);
}

void	*routine(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lock);
	while (philo->data->dead == 0)
	{
		eat(philo);
		if (check_condition(philo))
			return ((void *) 0);
		if (philo->data->meals_nb != -1 && philo->eat_cont
			>= philo->data->meals_nb)
			break ;
		print_message("is sleeping", philo);
		ft_usleep(philo->data->sleep_time);
		if (check_condition(philo))
			return ((void *) 0);
		print_message("is thinking", philo);
	}
	return ((void *) 0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = -1;
	data->start_time = get_time();
	if (pthread_create(&t0, NULL, &monitor, data))
		return (1);
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
		{
			ft_putstr("Failed to create philosopher thread\n");
			return (1);
		}
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (1);
	}
	if (pthread_join(t0, NULL))
		return (1);
	return (0);
}
