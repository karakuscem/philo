#include "philo.h"

int ft_init_sim(t_data *simulation, int argc, char **argv)
{
    simulation->number_of_philosophers = ft_atoi(argv[1]);
    simulation->time_to_die = ft_atoi(argv[2]);
    simulation->time_to_eat = ft_atoi(argv[3]);
    simulation->time_to_sleep = ft_atoi(argv[4]);
    simulation->someone_died = 0;
    gettimeofday(&simulation->start_time, NULL);
    if (argv[5])
        simulation->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else
        simulation->number_of_times_each_philosopher_must_eat = -1;
    simulation->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
    if (!simulation->forks)
        return (1);
    return (0);
}

int ft_init_mutex(t_data *simulation)
{
    int i;

    i = -1;
    while(++i < simulation->number_of_philosophers)
        pthread_mutex_init(&simulation->forks[i], NULL);
    pthread_mutex_init(&simulation->print_mutex, NULL);
    pthread_mutex_init(&simulation->someone_died_mutex, NULL);
    return (0);
}

int ft_init_philo(t_philo *philos, t_data *simulation)
{
    int i;

    i = -1;
    while (++i < simulation->number_of_philosophers)
    {
        philos[i].id = i + 1;
        philos[i].number_of_times_ate = 0;
        philos[i].left_fork = &simulation->forks[i];
        philos[i].right_fork = &simulation->forks[(i + 1) % simulation->number_of_philosophers];
        philos[i].simulation = simulation;
        pthread_mutex_init(&philos[i].times_ate_mutex, NULL);
        pthread_mutex_init(&philos[i].last_time_ate_mutex, NULL);
    }
    return (0);
}