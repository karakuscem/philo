#include "philo.h"

void    print_status(t_philo *philo, char *status)
{
    struct timeval current_time;
    int time_in_ms;

    pthread_mutex_lock(&philo->simulation->print_mutex);
    gettimeofday(&current_time, NULL);
    time_in_ms = (current_time.tv_sec - philo->simulation->start_time.tv_sec) * 1000 +
                 (current_time.tv_usec - philo->simulation->start_time.tv_usec) / 1000;
    printf("%llums %d %s\n", time_in_ms, philo->id, status);
    pthread_mutex_unlock(&philo->simulation->print_mutex);
}

void    *routine(void *arg)
{
    t_philo  *philo;

    philo = (t_philo *)arg;
    while (true)
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
        print_status(philo, "is eating");
        philo->number_of_times_ate++;
        usleep(philo->simulation->time_to_eat * 1000);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        print_status(philo, "is sleeping");
        usleep(philo->simulation->time_to_sleep * 1000);
        print_status(philo, "is thinking");
    }
    return (NULL);
}

int start_simulation(t_data *simulation)
{
    t_philo *philosophers;
    int     i;

    i = -1;
    philosophers = malloc(sizeof(t_philo) * simulation->number_of_philosophers);
    if (!philosophers)
        return (1);
    while (++i < simulation->number_of_philosophers)
    {
        philosophers[i].id = i + 1;
        philosophers[i].number_of_times_ate = 0;
        philosophers[i].left_fork = &simulation->forks[i];
        philosophers[i].right_fork = &simulation->forks[(i + 1) % simulation->number_of_philosophers];
        philosophers[i].simulation = simulation;
        if (pthread_create(&philosophers[i].thread, NULL, &routine, &philosophers[i]))
            return (1);
    }
    i = -1;
    while (++i < simulation->number_of_philosophers)
        pthread_join(philosophers[i].thread, NULL);
    free(philosophers);
    return (0);
}