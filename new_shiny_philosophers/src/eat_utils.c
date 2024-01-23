/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:10:04 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/23 02:11:56 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	forks_pickup(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->fork_left);
	else
		pthread_mutex_lock(philo->fork_right);
	ft_print_status(philo, FORK_EQUIP);
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->fork_right);
	else
		pthread_mutex_lock(philo->fork_left);
}

void	forks_putdown(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_unlock(philo->fork_left);
	else
		pthread_mutex_unlock(philo->fork_right);
	if (philo->id % 2 == 1)
		pthread_mutex_unlock(philo->fork_right);
	else
		pthread_mutex_unlock(philo->fork_left);
}
