/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:52:08 by duandrad          #+#    #+#             */
/*   Updated: 2025/10/13 15:52:09 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
}

void	print_message(char *message, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_unlock(&philo->data->write);
		return ;
	}
	printf("%zu %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->write);
}

void	ft_free(t_data *data, int flag)
{
	if (flag == 1 && data->tid)
		free(data->tid);
	else if (flag == 2 && data->tid && data->philos)
	{
		free(data->tid);
		free(data->philos);
	}
	else if (flag == 3 && data->tid && data->philos && data->forks)
	{
		free(data->tid);
		free(data->philos);
		free(data->forks);
	}
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
	ft_free(data, 3);
}
