/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:01:06 by duandrad          #+#    #+#             */
/*   Updated: 2025/03/19 20:05:50 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
  int philosophers;
  int forks;
  int eat_time;
  int sleep_time;
  int die_time;
}   t_philo;

int ft_atoi(char *str);
int ft_strlen(char *str);
void  ft_putstr(char *str);
t_philo *philo(void);

#endif // !HEADER_H

