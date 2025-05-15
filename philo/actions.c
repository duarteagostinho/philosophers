/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:30:39 by duandrad          #+#    #+#             */
/*   Updated: 2025/05/15 14:53:11 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo *philo)
{
	if (philo->eat_cont >= philo->data->meals_nb)
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

void	eat(t_philo *philo)
{
	if (philo->data->meals_nb != -1)
	{
		if (philo->eat_cont >= philo->data->meals_nb)
			return ;
	}
	if (philo->data->dead)
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = get_time();
	philo->eat_cont++;
	print_message("is eating", philo);
	if (philo->eat_cont == philo->data->meals_nb)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->finished++;
		pthread_mutex_unlock(&philo->data->lock);
	}
	pthread_mutex_unlock(&philo->lock);
	return ;
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
