#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
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
    bool someone_died;
    int id;
    int number_of_times_ate;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t print_mutex;
    pthread_mutex_t someone_died_mutex;
    struct timeval start_time;
} t_data;


int init_simulation(t_data *simulation, int argc, char **argv);
int init_mutexes(t_data *simulation, pthread_mutex_t *forks);
int start_simulation(t_data *simulation);

// Utils
int ft_atoi(const char *str);

#endif