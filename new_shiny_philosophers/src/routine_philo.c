/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:46:36 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 20:39:03 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	action_sleep(t_philo *philo, int64_t philo_sleep_time)
{
	uint64_t	sleep_until;

	sleep_until = philo_sleep_time + ft_save_time();
	ft_print_status(philo, SLEEP);
	while (ft_save_time() < sleep_until)
	{
		if (get_death_flag(philo->data) == 1)
			break ;
		ft_usleep(100);
	}
}

void	action_think(t_philo *philo, int visibility)
{
	int64_t	time_to_think;

	pthread_mutex_lock(&philo->lock_eating);
	time_to_think = (philo->data->time_to_die
					- (ft_save_time() - philo->last_meal)
					- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->lock_eating);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 00 && visibility == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (visibility == 1)
		ft_print_status(philo, THINK);
	action_sleep(philo, time_to_think);

	// (void) philo;
	// (void) visibility;
	// ft_print_status(philo, THINK);
}

void	action_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->locks_forks[philo->fork[0]]);
	ft_print_status(philo, FORK_EQUIP);
	pthread_mutex_lock(&philo->data->locks_forks[philo->fork[1]]);
	ft_print_status(philo, FORK_EQUIP);
	ft_print_status(philo, EAT);
	pthread_mutex_lock(&philo->lock_eating);
	philo->last_meal = ft_save_time();
	pthread_mutex_unlock(&philo->lock_eating);
	action_sleep(philo, philo->data->time_to_eat);
	if (get_death_flag(philo->data) != 1)
	{
		pthread_mutex_lock(&philo->lock_eating);
		philo->rounds_eaten++;
		pthread_mutex_unlock(&philo->lock_eating);
	}
	pthread_mutex_unlock(&philo->data->locks_forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->locks_forks[philo->fork[0]]);
}

void	*routine_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->locks_forks[philo->fork[0]]);
	ft_print_status(philo, FORK_EQUIP);
	ft_usleep(philo->data->time_to_die);
	ft_print_status(philo, DIE);
	pthread_mutex_unlock(&philo->data->locks_forks[philo->fork[0]]);
	return (NULL);
}

void	*routine_philo(void *philo_ptr)
{
	t_philo	*philo;
	
	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->lock_eating);
	philo->last_meal = philo->data->time_of_start;
	pthread_mutex_unlock(&philo->lock_eating);
	synchronize_start(philo->data->time_of_start);
	if (philo->data->philos_total == 1)
		return (routine_one(philo));
	if (philo->id % 2)                				//HERE??
		action_think(philo, 0);
	while(get_death_flag(philo->data) != 1)
	{
		action_eat(philo);
		if (get_death_flag(philo->data) != 1)
			action_sleep(philo, philo->data->time_to_sleep);
		if (get_death_flag(philo->data) != 1)
			action_think(philo, 1);
	}
	return (NULL);
}