/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:30:39 by duandrad          #+#    #+#             */
/*   Updated: 2025/05/05 19:35:53 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	pick_forks(t_philo *philo)
{
	if (philo->data->dead || philo->data->finished)
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo);
		if (philo->data->finished)
		{
			pthread_mutex_unlock(philo->l_fork);
			return;
		}
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo);
		if (philo->data->finished)
		{
			pthread_mutex_unlock(philo->r_fork);
			return;
		}
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo);
	}
}

void	eat(t_philo *philo)
{
	if (philo->data->dead || philo->data->finished == philo->data->philo_num)
		return ;
	pick_forks(philo);
	if (philo->data->dead)
	{
		drop_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->lock);
	print_message("is eating", philo);
	philo->last_meal = get_time();
	philo->eat_cont++;
	if (philo->eat_cont == philo->data->meals_nb)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->finished++;
		pthread_mutex_unlock(&philo->data->lock);
	}
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->data->eat_time);
	drop_forks(philo);
	return ;
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->data->dead || philo->data->finished)
		return ;
	print_message("is sleeping", philo);
	ft_usleep(philo->data->sleep_time);
}
