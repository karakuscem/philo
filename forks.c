#include "philo.h"

int acquire_forks_odd(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
	if (ft_print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
    if (philo->simulation->number_of_philosophers == 1)
    {
        pthread_mutex_unlock(philo->left_fork);
        usleep(philo->simulation->time_to_die * 1000);
        ft_print_status(philo, "died");
        return (1);
    }
	pthread_mutex_lock(philo->right_fork);
	if (ft_print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
    pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
    return (0);
}

int acquire_forks_even(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    if (ft_print_status(philo, "has taken a fork"))
    {
        pthread_mutex_unlock(philo->right_fork);
        return (1);
    }
    if (philo->simulation->number_of_philosophers == 1)
    {
        pthread_mutex_unlock(philo->right_fork);
        usleep(philo->simulation->time_to_die * 1000);
        ft_print_status(philo, "died");
        return (1);
    }
    pthread_mutex_lock(philo->left_fork);
    if (ft_print_status(philo, "has taken a fork"))
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return (1);
    }
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return (0);
}