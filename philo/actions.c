/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:30:39 by duandrad          #+#    #+#             */
/*   Updated: 2025/04/23 17:16:58 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
}

void	eat(t_philo *philo)
{
	if (philo->data->finished == 0)
	{
		pick_forks(philo);
		pthread_mutex_lock(&philo->lock);
		philo->eating = 1;
		philo->last_meal = get_time();
		print_message("is eating", philo);
		philo->eat_cont++;
		ft_usleep(philo->data->eat_time);
		philo->eating = 0;
		pthread_mutex_unlock(&philo->lock);
		drop_forks(philo);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_message("is sleeping", philo);
	ft_usleep(philo->data->sleep_time);
}
