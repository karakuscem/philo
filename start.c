#include "philo.h"

void print_status(t_data *simulation, char *status)
{
    struct timeval current_time;
    int time;

    pthread_mutex_lock(&simulation->print_mutex);
    gettimeofday(&current_time, NULL);
    time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
    printf("%d %d %s\n", time, simulation->id, status);
    pthread_mutex_unlock(&simulation->print_mutex);
}

void    *routine(void *arg)
{
    t_data *simulation;

    simulation = (t_data *)arg;
    while (1)
    {
        pthread_mutex_lock(simulation->left_fork);
        print_status(simulation, "has taken a fork");
        pthread_mutex_lock(simulation->right_fork);
        print_status(simulation, "has taken a fork");
        print_status(simulation, "is eating");
        usleep(simulation->time_to_eat * 1000);
        simulation->number_of_times_ate++;
        pthread_mutex_unlock(simulation->left_fork);
        pthread_mutex_unlock(simulation->right_fork);
        print_status(simulation, "is sleeping");
        usleep(simulation->time_to_sleep * 1000);
        print_status(simulation, "is thinking");
    }
}

int start_simulation(t_data *simulation)
{
    int i;

    i = 0;
    while (i < simulation->number_of_philosophers)
    {
        if (pthread_create(&simulation[i].thread, NULL, &routine, &simulation[i]))
            return (1);
        i++;
    }
    i = 0;
    while (i < simulation->number_of_philosophers)
    {
        if (pthread_join(simulation[i].thread, NULL))
            return (1);
        i++;
    }
}