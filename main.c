/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:01:27 by duandrad          #+#    #+#             */
/*   Updated: 2025/03/24 17:15:08 by gloryboydud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (checker(ac, av))
	{
		return (1);
		ft_putstr("checker error");
	}
	if (init_all(ac, av, &data))
	{
		return (1);
		ft_putstr("init all error");
	}
	if (thread_init(&data))
	{
		return (1);
		ft_putstr("thread init error");
	}
	ft_exit(&data);
	return (0);
}
