/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:30:39 by duandrad          #+#    #+#             */
/*   Updated: 2025/10/16 15:28:36 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_condition(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->data->meals_nb != -1)
	{
		if (philo->eat_cont >= philo->data->meals_nb)
		{
			pthread_mutex_unlock(&philo->lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	meals_completed(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->lock);
	result = (philo->data->meals_nb != -1
			&& philo->eat_cont >= philo->data->meals_nb);
	pthread_mutex_unlock(&philo->lock);
	return (result);
}

int	pick_forks(t_philo *philo)
{
	if (should_exit(philo))
		return (0);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo);
	}
	return (1);
}

void	eat(t_philo *philo)
{
	if (should_exit(philo))
		return ;
	if (meals_completed(philo))
		return ;
	if (!pick_forks(philo))
		return ;
	if (should_exit(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
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
	(pthread_mutex_unlock(philo->l_fork), pthread_mutex_unlock(philo->r_fork));
}
