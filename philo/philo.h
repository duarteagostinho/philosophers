/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:50:55 by duandrad          #+#    #+#             */
/*   Updated: 2025/10/13 15:50:55 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int					id;
	int					eat_cont;
	size_t				last_meal;
	size_t				time_to_die;
	struct s_data		*data;
	pthread_mutex_t		lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

typedef struct s_data
{
	int					philo_num;
	int					death_time;
	int					eat_time;
	int					sleep_time;
	int					meals_nb;
	int					dead;
	int					finished;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_t			*tid;
	size_t				start_time;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
}	t_data;

/*UTILS*/
int			ft_atoi(char *str);
int			checker(int ac, char **av);
size_t		get_time(void);
void		print_message(char *message, t_philo *philo);
void		ft_usleep(size_t ms);
void		ft_putstr(char *str);
void		ft_exit(t_data *data);

/* ACTIONS */
void		pick_forks(t_philo *philo);
void		eat(t_philo *philo);

/*INIT*/
int			init_all(int ac, char **av, t_data *data);
void		*routine(void *pt);
int			thread_init(t_data *data);
void		ft_free(t_data *data, int flag);
int			check_condition(t_philo *philo);
#endif
