/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarakus <ckarakus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:58:28 by ckarakus          #+#    #+#             */
/*   Updated: 2023/07/22 22:14:49 by ckarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				total_meals;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	times_ate_mutex;
	pthread_mutex_t	someone_died_mutex;
	struct timeval	start_time;
}	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	unsigned long long	last_time_ate;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		last_time_ate_mutex;
	t_data				*simulation;
}	t_philo;
// Init
int					ft_init_sim(t_data *simulation, int argc, char **argv);
int					ft_init_mutex(t_data *simulation);
int					ft_init_philo(t_philo *philos, t_data *simulation);

// Start
int					ft_start_sim(t_philo *philos, int num_of_philos);

// Utils
int					ft_atoi(const char *str);
int					ft_check_meals(t_philo *philos);
int					ft_check_death(t_philo *philo, int *someone_died);
int					ft_print_status(t_philo *philo, char *status);
int					acquire_forks_odd(t_philo *philo);
int					acquire_forks_even(t_philo *philo);
int					ft_end_sim(t_philo *philos, int num_of_philos);
int					ft_check_args(int argc, char **argv);
int					ft_simulation(t_data *simulation, t_philo *philos,
						int argc, char **argv);
void				ft_usleep(int wait_time);
void				ft_end_program(t_philo *philos, t_data *simulation);
unsigned long long	ft_real_time(t_philo *philo);
unsigned long long	ft_get_time(void);

#endif