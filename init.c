#include "philo.h"

int init_simulation(t_data *simulation, int argc, char **argv)
{
    int i;

    i = 0;
    simulation->number_of_philosophers = ft_atoi(argv[1]);
    simulation->time_to_die = ft_atoi(argv[2]);
    simulation->time_to_eat = ft_atoi(argv[3]);
    simulation->time_to_sleep = ft_atoi(argv[4]);
    simulation->someone_died = false;
    simulation->start_time = get_ms();
    if (argc == 6)
        simulation->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else
        simulation->number_of_times_each_philosopher_must_eat = -1;
    while (i < simulation->number_of_philosophers)
    {
        simulation[i].id = i + 1;
        simulation[i].number_of_times_ate = 0;
        i++;
    }
    return (0);
}

int init_mutexes(t_data *simulation, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    pthread_mutex_init(&simulation->print_mutex, NULL);
    pthread_mutex_init(&simulation->someone_died_mutex, NULL);
    while (i < simulation->number_of_philosophers)
    {
        simulation[i].left_fork = &forks[i];
		simulation[i].right_fork = &forks[(i + 1) % simulation->number_of_philosophers];
        i++;
    }
    i = 0;
    while (i < simulation->number_of_philosophers)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    return (0);
}