#include "philo.h"

void    print_status(t_data *simulation, char *status)
{
    unsigned long   time;

    time = get_real_time(simulation);
    printf("%llums %d %s\n", time, simulation->id, status);
}

void    routine(void *arg)
{
    t_data  *simulation;

    simulation = (t_data *)arg;
    pthread_mutex_lock(simulation->left_fork);
    print_status(simulation, " has taken a fork.\n");
    pthread_mutex_lock(simulation->right_fork);
    print_status(simulation, " has taken a fork.\n");
    print_status(simulation, " is eating");
    pthread_mutex_unlock(simulation->left_fork);
    pthread_mutex_unlock(simulation->right_fork);
    print_status(simulation, " is sleeping");
    usleep(simulation->time_to_sleep * 1000);
    print_status(simulation, " is thinking");
    usleep(simulation->time_to_eat * 1000);
    simulation->number_of_times_ate++;
}

int start_simulation(t_data *simulation)
{
    int i;

    i = 0;
    while (i < simulation->number_of_philosophers)
    {
        if (pthread_create(&simulation[i].thread, NULL, &routine, &simulation[i]));
            return (1);
        i++;
    }
    i = 0;
    while (i < simulation->number_of_philosophers)
    {
        if (pthread_join(&simulation[i].thread, NULL))
            return (1);
        i++;
    }
}