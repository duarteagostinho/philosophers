/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:01:39 by duandrad          #+#    #+#             */
/*   Updated: 2025/03/19 20:01:57 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_philo *philo(void)
{
  static t_philo  g;

  return (&g);
}

int ft_strlen(char *str)
{
  int i;

  i = 0;
  while(str[i])
    i++;
  return (i);
}

int ft_atoi(char *str)
{
  int i;
  int result;
  int sign;

  i = 0;
  result = 0;
  sign = 1;
  while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
    i++;
  if(str[i] == '+' || str[i] == '-')
  {
    if(str[i] == '-')
      sign = -1;
    i++;
  }
  while(str[i] >= '0' && str[i] <= '9' && str[i])
  {
    result *= 10;
    result += str[i] - '0';
    i++;
  }
  return (result * sign);
}

void  ft_putstr(char *str)
{
  int i;

  i = 0;
  while(str[i])
  {
    write(1, &str[i], 1);
    i++;
  }
}
