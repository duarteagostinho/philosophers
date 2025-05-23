/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mods.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:04:41 by duandrad          #+#    #+#             */
/*   Updated: 2025/05/16 13:41:18 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		if (philo->data->finished >= philo->data->philo_num)
		{
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	return (NULL);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;
	int i = 0;
	size_t calc;

	philo = (t_philo *) philo_pointer;
	while (philo->data->dead == 0 && philo->data->finished < philo->data->philo_num)
	{
		pthread_mutex_lock(&philo->lock);
		calc = (get_time() - philo->last_meal);
		if (calc >= philo->time_to_die)
		{
			print_message("has died", philo);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->lock);
		}
		pthread_mutex_unlock(&philo->lock);
		ft_usleep(10);
	}
	return ((void *)0);
}

void	*routine(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;

	while (philo->data->dead == 0)
	{
		eat(philo);
		if (philo->data->finished < philo->data->philo_num)
		{
			print_message("is sleeping", philo);
			ft_usleep(philo->data->sleep_time);
			print_message("is thinking", philo);
		}
	}
	if (pthread_join(philo->thread, NULL))
		return ((void *)1);
	return ((void *) 0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
		{
			ft_putstr("Failed to create philosopher thread\n");
			return (1);
		}
	}
	if (data->meals_nb > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
			return (1);
	}
	if (pthread_create(&data->philos->thread, NULL, &supervisor, data->philos))
		return (1);
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (1);
	}
	return (0);
}
