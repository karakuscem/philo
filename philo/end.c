#include "philo.h"

int ft_end_sim(t_philo *philos, int num_of_philos)
{
	int i;

	i = -1;
	while (++i < num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (1);
	}
	return (0);
}

void ft_end_program(t_philo *philos, t_data *simulation)
{
    int i;

    i = -1;
    while (++i < simulation->number_of_philosophers)
    {
        pthread_mutex_destroy(philos[i].left_fork);
        pthread_mutex_destroy(philos[i].right_fork);
        pthread_mutex_destroy(&philos[i].last_time_ate_mutex);
    }
    pthread_mutex_destroy(&philos->simulation->print_mutex);
    pthread_mutex_destroy(&philos->simulation->someone_died_mutex);
    pthread_mutex_destroy(&philos->simulation->times_ate_mutex);
    pthread_mutex_destroy(philos->simulation->forks);
    free(philos);
    free(simulation->forks);
    free(simulation);
}