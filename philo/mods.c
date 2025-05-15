/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mods.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:04:41 by duandrad          #+#    #+#             */
/*   Updated: 2025/05/15 17:36:42 by duandrad         ###   ########.fr       */
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
		ft_usleep(10);
	}
	return (NULL);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (philo->data->dead == 0 && philo->data->finished < philo->data->philo_num)
	{
		pthread_mutex_lock(&philo->lock);
		if ((get_time() - philo->last_meal) >= philo->time_to_die)
		{
			printf("DEBUG: Philosopher %d last meal: %zu, current time: %zu\n",
				philo->id, philo->last_meal - philo->data->start_time, get_time() - philo->data->start_time);
			print_message("has died", philo);
			philo->data->dead = 1;
		}
		pthread_mutex_unlock(&philo->lock);
		ft_usleep(100);
	}
	return ((void *)0);
}

void	*routine(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;
	if (pthread_create(&philo->thread, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		pick_forks(philo);
		eat(philo);
		print_message("is sleeping", philo);
		ft_usleep(philo->data->eat_time);
		print_message("is thinking", philo);
		ft_usleep(philo->data->sleep_time);
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
	if (data->meals_nb > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
			return (1);
	}
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
		{
			ft_putstr("Failed to create philosopher thread\n");
			return (1);
		}
		ft_usleep(100);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (1);
	}
	return (0);
}
