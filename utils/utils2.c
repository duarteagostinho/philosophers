/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:42:45 by duandrad          #+#    #+#             */
/*   Updated: 2025/04/15 18:14:39 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	if ((get_time() - start) < ms)
		usleep(ms / 10);
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

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (philo->data->dead == 0)
		printf("Philo %d %s at %u\n", philo->id, message, time);
	pthread_mutex_unlock(&philo->data->write);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while(str[++i])
		write(1, &str[i], 1);
}