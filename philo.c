#include "philo.h"

// Create a struct for store necessary data.
// Take arguments and place them in struct. (Init function)
// Create a routine function
// Create a print function
// Create a start simulation function
// Create a free simulation function


// Init simulation
int init_simulation(t_data *simulation, int argc, char **argv)
{
    simulation->number_of_philosophers = atoi(argv[1]);
    simulation->time_to_die = atoi(argv[2]);
    simulation->time_to_eat = atoi(argv[3]);
    simulation->time_to_sleep = atoi(argv[4]);
    if (argc == 6)
        simulation->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
    else
        simulation->number_of_times_each_philosopher_must_eat = -1;
    simulation->someone_died = false;
    return (0);
}

// Create thread and finish with join
int init_philos(t_philo *philos, t_data *simulation)
{
    int i;
    int j;

    philos = malloc(sizeof(t_philo) * simulation->number_of_philosophers);
    i = 0;
    j = 0;
    while (i < simulation->number_of_philosophers)
    {
        philos[i].id = i + 1;
        philos[i].number_of_times_ate = 0;
        philos[i].left_fork = &simulation->forks[i];
        philos[i].right_fork = &simulation->forks[(i + 1) % simulation->number_of_philosophers];
        philos[i].simulation = simulation;
        if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
            return (1);
    }
    while (j < simulation->number_of_philosophers)
        pthread_join(philos[i].thread, NULL);
    return (0);
}

// Print status
void    print_status(t_philo *philo, char *status)
{

}

// routine
void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
    }
    return (NULL);
}

// Gonna rewrite it
int start_simulation(t_data *simulation)
{
    pthread_t   th[4];
    int i;

    for (i = 0; i < 4; i++)
    {
        if (pthread_create(th+i, NULL, &routine, NULL) != 0)
            return (1);
        printf("Thred %d has started\n", i);
    }
    for (i = 0; i < 4; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            return (2);
        printf("Thread %d has finished\n", i);
    }
}

int main(int argc, char **argv)
{
    t_data  *simulation;
    t_philo *philos;

    if (argc < 5 || argc > 6)
        return (1);
    simulation = malloc(sizeof(t_data));
    if (!simulation)
        return (1);
    if (init_simulation(simulation, argc, argv))
        return (1);
    if (start_simulation(simulation))
        return (1);
    return (0);
}
