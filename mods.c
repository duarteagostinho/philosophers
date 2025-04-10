/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mods.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:04:41 by duandrad          #+#    #+#             */
/*   Updated: 2025/04/10 19:33:17 by duandrad         ###   ########.fr       */
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
	while (philo->data->dead == 0)
	{
		eat(philo);
		print_message("is thinking", philo);
	}
	if (pthread_join(&philo->thread, NULL))
		return ((void*)1);
	return (NULL);
}