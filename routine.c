/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:30:39 by duandrad          #+#    #+#             */
/*   Updated: 2025/03/25 16:57:06 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((unsigned int)(tv.tv_usec * 1000) + (tv.tv_sec / 1000));
}

void	eating(t_data *data)
{
	
}
void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	printf("philo %d has taken a fork\n");
	pthread_mutex_lock(&philo->r_fork);
	printf("Philo %d has taken a fork\n");
	
}
