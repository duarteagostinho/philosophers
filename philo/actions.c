/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:30:39 by duandrad          #+#    #+#             */
/*   Updated: 2025/07/21 19:42:51 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo *philo)
{
	if (philo->data->meals_nb != -1)
	{
		if (philo->eat_cont >= philo->data->meals_nb)
			return ;
	}
	if (philo->data->dead)
		return ;
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
}

static int	check_condition(t_philo *philo)
{
	if (philo->data->meals_nb != -1)
	{
		if (philo->eat_cont >= philo->data->meals_nb)
			return (1);
	}
	if (philo->data->dead)
		return (1);
	return (0);
}

void	eat(t_philo *philo)
{
	if (check_condition(philo))
		return ;
	pick_forks(philo);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
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
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return ;
}
