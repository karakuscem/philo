/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarakus <ckarakus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:58:30 by ckarakus          #+#    #+#             */
/*   Updated: 2023/07/21 22:58:31 by ckarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_simulation(t_data *simulation, t_philo *philos, int argc, char **argv)
{
    if (ft_init_sim(simulation, argc, argv))
        return (1);
    if (ft_init_mutex(simulation))
        return (1);
    if (ft_init_philo(philos, simulation))
        return (1);
    if (ft_start_sim(philos, simulation->number_of_philosophers))
        return (1);
    if (ft_end_sim(philos, simulation->number_of_philosophers))
        return (1);
    ft_end_program(philos, simulation);
    return (0);
}