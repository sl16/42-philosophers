/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:46:36 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 22:46:48 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	action_sleep(t_philo *philo, int64_t philo_sleep_time)
{
	// uint64_t	sleep_until;

	// sleep_until = philo_sleep_time + ft_save_time();
	// ft_print_status(philo, SLEEP);
	// while (ft_save_time() < sleep_until)
	// {
	// 	if (get_death_flag(philo->data) == 1)
	// 		break ;
	// 	ft_usleep(100);
	// }

	ft_print_status(philo, SLEEP);
	ft_usleep(philo_sleep_time);
}

void	action_think(t_philo *philo, int visibility)
{
	// int64_t	time_to_think;

	// pthread_mutex_lock(&philo->lock_philo);
	// time_to_think = (philo->data->time_to_die
	// 				- (ft_save_time() - philo->last_meal)
	// 				- philo->data->time_to_eat) / 2;
	// pthread_mutex_unlock(&philo->lock_philo);
	// if (time_to_think < 0)
	// 	time_to_think = 0;
	// if (time_to_think == 00 && visibility == 0)
	// 	time_to_think = 1;
	// if (time_to_think > 600)
	// 	time_to_think = 200;
	// if (visibility == 1)
	// 	ft_print_status(philo, THINK);
	// action_sleep(philo, time_to_think);

	(void) visibility;
	ft_print_status(philo, THINK);
}

void	action_eat(t_philo *philo)
{
	// if (philo->id % 2 == 0)
	// 	pthread_mutex_lock(philo->fork_left);
	// else
	// 	pthread_mutex_lock(philo->fork_right);
	// ft_print_status(philo, FORK_EQUIP);
	// if (philo->id % 2 == 0)
	// 	pthread_mutex_lock(philo->fork_right);
	// else
	// 	pthread_mutex_lock(philo->fork_left);
	// ft_print_status(philo, FORK_EQUIP);

	if (philo->id != 1)
	{
		pthread_mutex_lock(philo->fork_left);
		ft_print_status(philo, FORK_EQUIP);
		// set_eating_flag(philo, 1);
		pthread_mutex_lock(philo->fork_right);
		ft_print_status(philo, FORK_EQUIP);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		ft_print_status(philo, FORK_EQUIP);
		// set_eating_flag(philo, 1);
		pthread_mutex_lock(philo->fork_left);
		ft_print_status(philo, FORK_EQUIP);
	}
	// set_eating_flag(philo, 1);
	ft_print_status(philo, EAT);
	pthread_mutex_lock(&philo->lock_philo);
	philo->last_meal = ft_save_time();
	pthread_mutex_unlock(&philo->lock_philo);
	action_sleep(philo, philo->data->time_to_eat);
	// set_eating_flag(philo, 0);
	if (get_death_flag(philo->data) != 1)
	{
		pthread_mutex_lock(&philo->lock_philo);
		philo->rounds_eaten++;
		pthread_mutex_unlock(&philo->lock_philo);
	}
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
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
	// ft_usleep((uint64_t) philo->id);
	pthread_mutex_lock(&philo->lock_philo);
	philo->last_meal = philo->data->time_of_start;
	pthread_mutex_unlock(&philo->lock_philo);
	synchronize_start(philo->data->time_of_start);
	if (philo->data->philos_total == 1)
		return (routine_one(philo));
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	while(get_death_flag(philo->data) != 1)
	{
		action_eat(philo);
		// if (get_death_flag(philo->data) != 1)
		action_sleep(philo, philo->data->time_to_sleep);
		// if (get_death_flag(philo->data) != 1)
		action_think(philo, 1);
	}
	return (NULL);
}