#include "philo.h"

int main(int argc, char **argv)
{
    t_data  *simulation;
    pthread_mutex_t *forks;
    
    forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
    if (!forks)
        return (1);
    simulation = malloc(sizeof(t_data) * ft_atoi(argv[1]));
    if (!simulation)
        return (1);
    if (argc < 5 || argc > 6)
        return (1);
    if (init_simulation(simulation, argc, argv))
        return (1);
    if (init_mutexes(simulation, forks))
        return (1);
    if (start_simulation(simulation))
        return (1);
    return (0);
}
