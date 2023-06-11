#include "philo.h"

int ft_print_status(t_philo *philo, char *status)
{
    unsigned long long time_in_ms;

    pthread_mutex_lock(&philo->simulation->print_mutex);
    time_in_ms = ft_real_time(philo);
    ft_check_death(philo, &philo->simulation->someone_died);
    if (philo->simulation->someone_died == 0)
        printf("%llu %d %s\n", time_in_ms, philo->id, status);
    else
    {
        pthread_mutex_unlock(&philo->simulation->print_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->simulation->print_mutex);
    return (0);
}


int main(int argc, char **argv)
{
    t_data  *simulation;
    t_philo *philos;

    if (argc < 5 || argc > 6)
        return (1);
    simulation = malloc(sizeof(t_data) * 1);
    if (!simulation)
        return (1);
    if (ft_init_sim(simulation, argc, argv))
        return (1);
    philos = malloc(sizeof(t_philo) * simulation->number_of_philosophers);
    if (!philos)
        return (1);
    if (ft_init_mutex(simulation))
        return (1);
    if (ft_init_philo(philos, simulation))
        return (1);
    if (ft_start_sim(philos, simulation->number_of_philosophers))
        return (1);
    return (0);
}