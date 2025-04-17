/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mods.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:04:41 by duandrad          #+#    #+#             */
/*   Updated: 2025/04/15 22:48:37 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *pt)
{
	t_philo	*philo;
	size_t	last_meal;

	philo = (t_philo *)pt;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
		{
			philo->data->dead = 1;
			print_message("has died", philo);
		}
		if (philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*monitor(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;
	while (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >=  philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*routine(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_create(&philo->thread, NULL, &supervisor, (void*)philo);
	return ((void *)1);
	ft_putstr("routine\n");
	while (philo->data->dead == 0)
	{
		eat(philo);
		print_message("is thinking", philo);
	}
	if (pthread_join(philo->thread, NULL))
		return ((void*)1);
	return (NULL);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = -1;
	data->start_time = get_time();
	if (data->meals_nb > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
			return (1);
	}
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (1);
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (1);
	}
	return (0);
}