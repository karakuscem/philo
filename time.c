#include "philo.h"

unsigned long long ft_real_time(t_philo *philo)
{
    struct timeval current_time;
    unsigned long long time_in_ms;

    gettimeofday(&current_time, NULL);
    time_in_ms = (current_time.tv_sec - philo->simulation->start_time.tv_sec) * 1000;
    time_in_ms += (current_time.tv_usec - philo->simulation->start_time.tv_usec) / 1000;
    return (time_in_ms);
}

unsigned long long ft_get_time(void)
{
    struct timeval current_time;
    unsigned long long time_in_ms;

    gettimeofday(&current_time, NULL);
    time_in_ms = (current_time.tv_sec * 1000);
    time_in_ms += (current_time.tv_usec / 1000);
    return (time_in_ms);
}

int ft_usleep(unsigned long long time_in_ms)
{
    unsigned long long start;

    start = ft_get_time();
    while (ft_get_time() - start < time_in_ms)
    {
        if (usleep(100) == -1)
            return (1);
    }
    return (0);
}