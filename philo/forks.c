/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarakus <ckarakus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:58:17 by ckarakus          #+#    #+#             */
/*   Updated: 2023/07/22 18:13:28 by ckarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        ft_usleep(philo->simulation->time_to_die);
        ft_check_death(philo, &philo->simulation->someone_died);
        return (1);
    }
	pthread_mutex_lock(philo->right_fork);
	if (ft_print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
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
        ft_usleep(philo->simulation->time_to_die);
        ft_check_death(philo, &philo->simulation->someone_died);
        return (1);
    }
    pthread_mutex_lock(philo->left_fork);
    if (ft_print_status(philo, "has taken a fork"))
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return (1);
    }
    return (0);
}