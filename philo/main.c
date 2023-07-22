/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarakus <ckarakus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:58:23 by ckarakus          #+#    #+#             */
/*   Updated: 2023/07/22 23:37:20 by ckarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_status(t_philo *philo, char *status)
{
	unsigned long long	time_in_ms;

	pthread_mutex_lock(&philo->simulation->print_mutex);
	time_in_ms = ft_real_time(philo);
	pthread_mutex_lock(&philo->simulation->someone_died_mutex);
	if (philo->simulation->someone_died == 0)
	{
		printf("%llu %d %s\n", time_in_ms, philo->id, status);
		pthread_mutex_unlock(&philo->simulation->someone_died_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->simulation->someone_died_mutex);
		pthread_mutex_unlock(&philo->simulation->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->simulation->print_mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*simulation;
	t_philo	*philos;

	if (ft_check_args(argc, argv))
	{
		printf("Arg Error\n");
		return (1);
	}
	simulation = malloc(sizeof(t_data));
	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!simulation || !philos)
		return (1);
	if (ft_simulation(simulation, philos, argc, argv))
		return (1);
	return (0);
}
