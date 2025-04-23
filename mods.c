/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mods.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:04:41 by duandrad          #+#    #+#             */
/*   Updated: 2025/04/23 16:02:10 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *) 0);
}

void	*supervisor(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if ((get_time() - philo->last_meal) > philo->time_to_die)
			print_message("has died", philo);
		pthread_mutex_unlock(&philo->lock);
		ft_usleep(100);
	}
	return ((void *) 0);
}


void	*routine(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;
	if (pthread_create(&philo->thread, NULL, &supervisor, (void *)philo))
	{
		ft_putstr("Failed to create supervisor thread\n");
		return ((void *)1);
	}
	while (philo->data->dead == 0)
	{
		eat(philo);
		if (philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		print_message("is thinking", philo);
	}
	if (pthread_join(philo->thread, NULL))
	{
		ft_putstr("Failed to join supervisor thread\n");
		return ((void *)1);
	}
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
