/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:30:39 by duandrad          #+#    #+#             */
/*   Updated: 2025/03/24 19:48:05 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((unsigned int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	loop(t_data *data)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (1)
	{
		while (i < data->meals_nb)
		{
			printf("%d Philosopher %d is thinking\n", get_time(), data->philos[j]);
			j++;
			i++;
		}
		break;
	}
}