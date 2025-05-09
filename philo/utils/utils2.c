/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:42:45 by duandrad          #+#    #+#             */
/*   Updated: 2025/05/05 16:53:15 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_usleep(useconds_t ms)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_message(char *message, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_unlock(&philo->data->write);
		return ;
	}
	pthread_mutex_unlock(&philo->data->lock);
	time = get_time() - philo->data->start_time;
	printf("%zu %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->data->write);
}

void	ft_free(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	ft_free(data);
}
