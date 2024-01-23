/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:46:36 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/23 02:21:13 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	action_sleep(t_philo *philo, int64_t philo_sleep_time)
{
	ft_print_status(philo, SLEEP);
	ft_usleep(philo_sleep_time);
}

void	action_think(t_philo *philo)
{
	int64_t	think_time;

	pthread_mutex_lock(&philo->lock_philo);
	if (philo->data->philos_total % 2 == 0)
		think_time = philo->data->time_to_eat - philo->data->time_to_sleep;
	else
		think_time = philo->data->time_to_eat * 2 - philo->data->time_to_sleep;
	pthread_mutex_unlock(&philo->lock_philo);
	if (think_time < 0)
		think_time = 0;
	ft_print_status(philo, THINK);
	ft_usleep(think_time);
}

void	action_eat(t_philo *philo)
{
	forks_pickup(philo);
	ft_print_status(philo, FORK_EQUIP);
	ft_print_status(philo, EAT);
	pthread_mutex_lock(&philo->lock_philo);
	philo->last_meal = ft_save_time();
	pthread_mutex_unlock(&philo->lock_philo);
	ft_usleep(philo->data->time_to_eat);
	if (get_death_flag(philo->data) != 1)
	{
		pthread_mutex_lock(&philo->lock_philo);
		philo->rounds_eaten++;
		pthread_mutex_unlock(&philo->lock_philo);
	}
	forks_putdown(philo);
}

void	*routine_one(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	ft_print_status(philo, FORK_EQUIP);
	ft_usleep(philo->data->time_to_die);
	ft_print_status(philo, DIE);
	pthread_mutex_unlock(philo->fork_left);
	return (NULL);
}

void	*routine_philo(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	synchronize_start(philo->data->time_of_start);
	if (philo->data->philos_total == 1)
		return (routine_one(philo));
	if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat);
	while (get_death_flag(philo->data) != 1)
	{
		action_eat(philo);
		action_sleep(philo, philo->data->time_to_sleep);
		action_think(philo);
	}
	return (NULL);
}
