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
    }
    return (0);
}

unsigned long long ft_real_time(t_philo *philo)
{
    struct timeval current_time;
    unsigned long long time_in_ms;

    gettimeofday(&current_time, NULL);
    time_in_ms = (current_time.tv_sec - philo->simulation->start_time.tv_sec) * 1000;
    time_in_ms += (current_time.tv_usec - philo->simulation->start_time.tv_usec) / 1000;
    return (time_in_ms);
}

void    ft_print_status(t_philo *philo, char *status)
{
    unsigned long long time_in_ms;

    pthread_mutex_lock(&philo->simulation->print_mutex);
    time_in_ms = ft_real_time(philo);
    printf("%llums %d %s\n", time_in_ms, philo->id, status);
    pthread_mutex_unlock(&philo->simulation->print_mutex);
}

int ft_check_meals(t_philo *philos)
{
    if (philos->simulation->number_of_times_each_philosopher_must_eat != -1)
    {
        if (philos->number_of_times_ate >= philos->simulation->number_of_times_each_philosopher_must_eat)
            return (1);
    }
    return (0);
}

int ft_check_death(t_philo *philos)
{
    unsigned long long time_in_ms;

    time_in_ms = ft_real_time(philos);
    if (time_in_ms - philos->last_time_ate > philos->simulation->time_to_die)
    {
        ft_print_status(philos, "died");
        pthread_mutex_lock(&philos->simulation->someone_died_mutex);
        philos->simulation->someone_died = 1;
        pthread_mutex_unlock(&philos->simulation->someone_died_mutex);
        return (1);
    }
    return (0);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (ft_check_meals(philo) || ft_check_death(philo))
            break;
        pthread_mutex_lock(philo->right_fork);
        ft_print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        ft_print_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->simulation->someone_died_mutex);
        philo->last_time_ate = ft_real_time(philo);
        pthread_mutex_unlock(&philo->simulation->someone_died_mutex);
        ft_print_status(philo, "is eating");
        usleep(philo->simulation->time_to_eat * 1000);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_lock(&philo->times_ate_mutex);
        philo->number_of_times_ate++;
        pthread_mutex_unlock(&philo->times_ate_mutex);
        ft_print_status(philo, "is sleeping");
        usleep(philo->simulation->time_to_sleep * 1000);
        ft_print_status(philo, "is thinking");
    }
} 

int ft_start_sim(t_philo *philos, int num_of_philos)
{
    int i;

    i = -1;
    while (++i < num_of_philos)
    {
        if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
            return (1);
        usleep(100);
    }
    i = -1;
    while (++i < num_of_philos)
        pthread_join(philos[i].thread, NULL);
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
    free(simulation->forks);
    free(simulation);
    
    return (0);
}