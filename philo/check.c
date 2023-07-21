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
        pthread_mutex_lock(&philo->simulation->someone_died_mutex);
        philo->simulation->someone_died = 1;
        pthread_mutex_unlock(&philo->simulation->someone_died_mutex);
        pthread_mutex_unlock(&philo->simulation->times_ate_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->simulation->times_ate_mutex);
    return (0);
}


int ft_check_death(t_philo *philo, int *someone_died)
{
    unsigned long long time_in_ms;
    int                eaten;
    int                time_to_die;

    pthread_mutex_lock(&philo->last_time_ate_mutex);
    eaten = philo->last_time_ate;
    pthread_mutex_unlock(&philo->last_time_ate_mutex);
    time_to_die = philo->simulation->time_to_die;
    time_in_ms = ft_real_time(philo);

    if (ft_check_meals(philo) || ((int)(time_in_ms - eaten) > time_to_die && *someone_died == 0))
    {
        pthread_mutex_lock(&philo->simulation->someone_died_mutex);
        printf("%llu %d died\n", time_in_ms, philo->id);
        *someone_died = 1;
        pthread_mutex_unlock(&philo->simulation->someone_died_mutex);
        return (1);
    }
    return (0);
}

static int ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static int ft_check_valid(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (!ft_isdigit(argv[i][j]))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int ft_check_args(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (1);
    if (ft_check_valid(argc, argv))
        return (1);
    return (0);
}