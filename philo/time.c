/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarakus <ckarakus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:58:35 by ckarakus          #+#    #+#             */
/*   Updated: 2023/07/21 22:58:36 by ckarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_usleep(int wait_time)
{
	unsigned long long	time;

	time = ft_get_time();
	while (ft_get_time() - time < (unsigned long long)wait_time)
		usleep(100);
}