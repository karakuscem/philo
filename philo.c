#include "philo.h"

// Create a struct for store necessary data.
// Take arguments and place them in struct. (Init function)
// Create a routine function
// Create a print function
// Create a start simulation function
// Create a free simulation function

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

void    *routine(void *arg)
{
    t_data *simulation;

    simulation = (t_data *)arg;
    printf("Hello from thread\n");
    return (NULL);
}

int start_simulation(t_data *simulation)
{
    pthread_t   th[4];
    int i;

    for (i = 0; i < 4; i++)
    {
        if (pthread_create(th+i, NULL, &routine, NULL) != 0)
            return (1);
        if (pthread_join(th[i], NULL) != 0)
            return (2);
    }
}

int main(int argc, char **argv)
{
    t_data *simulation;

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
