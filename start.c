#include "philo.h"

int ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (acquire_forks_even(philo))
			return (1);
	}
	else
		if (acquire_forks_odd(philo))
			return (1);
	if  (ft_print_status(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->simulation->times_ate_mutex);
	philo->simulation->total_meals++;
	pthread_mutex_unlock(&philo->simulation->times_ate_mutex);
	return (0);
}

int ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_time_ate_mutex);
	philo->last_time_ate = ft_real_time(philo);
	pthread_mutex_unlock(&philo->last_time_ate_mutex);
	ft_usleep(philo->simulation->time_to_eat);
	if (ft_print_status(philo, "is sleeping"))
		return (1);
	ft_usleep(philo->simulation->time_to_sleep);
	return (0);
}

int ft_think(t_philo *philo)
{
	if (ft_print_status(philo, "is thinking"))
		return (1);
	return (0);
}

static void    *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_eat(philo))
			break;
		if (ft_sleep(philo))
			break;
		if (ft_think(philo))
			break;
	}
	return (NULL);
} 

int ft_start_sim(t_philo *philos, int num_of_philos)
{
	int i;

	i = -1;
	while (++i < num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
			return (1);
	}
	i = -1;
	while (++i < num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (1);
	}
	return (0);
}