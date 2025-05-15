/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duandrad <duandrad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:01:06 by duandrad          #+#    #+#             */
/*   Updated: 2025/03/25 20:19:20 by duandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

struct	s_data;

typedef struct s_philo
{
	int					id;
	int					eat_cont;
	int					status;
	int					eating;
	size_t				last_meal;
	size_t				time_to_die;
	struct s_data		*data;
	pthread_t			thread;
	pthread_mutex_t		lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

typedef struct s_data
{
	int					philo_num;
	unsigned int		death_time;
	unsigned int		eat_time;
	unsigned int		sleep_time;
	int					meals_nb;
	int					dead;
	int					all_finished;
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
int			ft_strlen(char *str);
int			ft_isdigit(char c);
int			checker(int ac, char **av);
size_t		get_time(void);
void		print_message(char *message, t_philo *philo);
void		ft_usleep(size_t ms);
void		ft_putstr(char *str);
void		ft_exit(t_data *data);

/* ACTIONS */
void		pick_forks(t_philo *philo);
void		eat(t_philo *philo);
void		drop_forks(t_philo *philo);

/*INIT*/
int			init_all(int ac, char **av, t_data *data);
void		*routine(void *pt);
int			thread_init(t_data *data);

#endif
