#include "philo.h"

int init_simulation(t_data *simulation, int argc, char **argv)
{
    int i;

    i = -1;
    simulation->number_of_philosophers = ft_atoi(argv[1]);
    simulation->time_to_die = ft_atoi(argv[2]);
    simulation->time_to_eat = ft_atoi(argv[3]);
    simulation->time_to_sleep = ft_atoi(argv[4]);
    simulation->number_of_times_each_philosopher_must_eat = argc == 6 ? ft_atoi(argv[5]) : -1;
    simulation->someone_died = false;
    simulation->forks = malloc(sizeof(pthread_mutex_t) * simulation->number_of_philosophers);
    if (!simulation->forks)
        return (1);
    while (++i < simulation->number_of_philosophers)
        pthread_mutex_init(&simulation->forks[i], NULL);
    pthread_mutex_init(&simulation->print_mutex, NULL);
    pthread_mutex_init(&simulation->someone_died_mutex, NULL);
    gettimeofday(&simulation->start_time, NULL);
    return (0);
}
