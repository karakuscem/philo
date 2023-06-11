#include "philo.h"

int ft_check_meals(t_philo *philo)
{
    pthread_mutex_lock(&philo->times_ate_mutex);
    if (philo->number_of_times_ate >= philo->simulation->number_of_times_each_philosopher_must_eat)
    {
        philo->simulation->someone_died = 1;
        pthread_mutex_unlock(&philo->times_ate_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->times_ate_mutex);
    return (0);
}

int ft_check_death(t_philo *philo, int *someone_died)
{
    unsigned long long time_in_ms;

    time_in_ms = ft_real_time(philo);
    ft_check_meals(philo);
    if (philo->simulation->someone_died == 1)
        return (1);
    else if ((time_in_ms - philo->last_time_ate) > philo->simulation->time_to_die)
    {
        printf("%llu %d %s\n", time_in_ms, philo->id, "died");
        *someone_died = 1;
        return (1);
    }
    return (0);
}

