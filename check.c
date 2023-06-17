#include "philo.h"

int ft_check_meals(t_philo *philo)
{
    int must_eat;
    int total_meals;
    int philo_nums;

    pthread_mutex_lock(&philo->simulation->times_ate_mutex);
    must_eat = philo->simulation->number_of_times_each_philosopher_must_eat;
    total_meals = philo->simulation->total_meals;
    philo_nums = philo->simulation->number_of_philosophers;
    if (must_eat > -1 && total_meals >= must_eat * philo_nums)
    {
        philo->simulation->someone_died = 1;
        pthread_mutex_unlock(&philo->simulation->times_ate_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->simulation->times_ate_mutex);
    return (0);
}

int ft_check_death(t_philo *philo, int *someone_died)
{
    unsigned long long time_in_ms;

    time_in_ms = ft_real_time(philo);
    if (philo->simulation->someone_died == 1)
        return (1);
    else if (ft_check_meals(philo))
        return (1);
    else if ((int)(time_in_ms - philo->last_time_ate) > philo->simulation->time_to_die)
    {
        if (philo->simulation->someone_died == 0)
        {
            ft_print_status(philo, "died");
            *someone_died = 1;
            return (1);
        }
    }
    return (0);
}