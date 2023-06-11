#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int someone_died;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t someone_died_mutex;
    struct timeval start_time;
} t_data;

typedef struct s_philo
{
    int id;
    int number_of_times_ate;
    pthread_t thread;
    unsigned long long last_time_ate;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t times_ate_mutex;
    pthread_mutex_t last_time_ate_mutex;
    t_data *simulation;
} t_philo;


// Init
int ft_init_sim(t_data *simulation, int argc, char **argv);
int ft_init_mutex(t_data *simulation);
int ft_init_philo(t_philo *philos, t_data *simulation);

// Start
int ft_start_sim(t_philo *philos, int num_of_philos);

// Utils
int ft_atoi(const char *str);
int ft_check_meals(t_philo *philos);
int ft_check_death(t_philo *philo, int *someone_died);
unsigned long long ft_real_time(t_philo *philo);
int ft_print_status(t_philo *philo, char *status);

#endif