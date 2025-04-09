/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:42:45 by duandrad          #+#    #+#             */
/*   Updated: 2025/04/08 17:18:06 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(size_t ms)
{
	
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(char *message, t_philo *philo)
{
	unsigned int	time;

	time = get_time();
	pthread_mutex_lock(&philo->data->write);
	printf("%d %s\n", philo->id, message);
}