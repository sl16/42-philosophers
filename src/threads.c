/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:26:25 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/17 22:22:37 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// ft_round_check
// - checks if all philosophers have reached required number of rounds;
// - if all have eaten sufficiently, stops the simulation (via death_flag);
void	*ft_round_check(void *data_ptr)
{
	t_data	*data;

	data = (t_data *) data_ptr;
	while (get_death_flag(data) != 1)
	{
		pthread_mutex_lock(&data->access_data);
		if (get_philos_finished(data) == data->philos_total)
			set_death_flag(data);
		pthread_mutex_unlock(&data->access_data);
	}
	return (NULL);
}

// ft_philo_check
// - checks philosopher if they have died;
// - checks if they have eaten required number of rounds;
void	*ft_philo_check(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (get_death_flag(philo->data) != 1)
	{
		pthread_mutex_lock(&philo->access_philo);
		if (ft_save_time() >= philo->death_timer && get_eating_flag(philo) != 1)
		{
			set_death_flag(philo->data);
			ft_print_status(philo, DIED);
		}
		if (philo->rounds_eaten == philo->data->rounds_total)
		{
			pthread_mutex_lock(&philo->data->access_data);
			philo->data->philos_finished++;
			philo->rounds_eaten++;
			pthread_mutex_unlock(&philo->data->access_data);
		}
		pthread_mutex_unlock(&philo->access_philo);
	}
	return (NULL);
}

// ft_eat
// - odd philos pick left fork first, even ones pick right (prevents deadlock);
// - eats, sleeps, thinks;
void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->fork_right);
	else
		pthread_mutex_lock(philo->fork_left);
	if (get_death_flag(philo->data) != 1)
		ft_print_status(philo, FORK_EQUIP);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->fork_left);
	else
		pthread_mutex_lock(philo->fork_right);
	if (get_death_flag(philo->data) != 1)
		ft_print_status(philo, FORK_EQUIP);
	if (get_death_flag(philo->data) != 1)
	{
		pthread_mutex_lock(&philo->access_philo);
		set_eating_flag_on(philo);
		philo->death_timer = ft_save_time() + philo->data->time_to_die;
		ft_print_status(philo, EATING);
		ft_usleep(philo->data->time_to_eat);
		philo->rounds_eaten++;
		set_eating_flag_off(philo);
		pthread_mutex_unlock(&philo->access_philo);
	}
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

// ft_philosopher
// - cast and assign passed pointer to philo struct;
// - calculate initial time until death;
// - create a separate thread that chekcs for death (ft_philo_check);
// - eat, sleep, think until death (or all rounds finished);
void	*ft_philosopher(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->death_timer = philo->data->time_to_die + ft_save_time();
	ft_generate_checker(philo);
	while (get_death_flag(philo->data) != 1)
	{
		if (philo->data->philos_total == 1)
			ft_routine_only_one(philo);
		else
			ft_eat(philo);
		if (get_death_flag(philo->data) != 1)
		{
			ft_print_status(philo, SLEEPING);
			ft_usleep(philo->data->time_to_sleep);
		}
		if (get_death_flag(philo->data) != 1)
			ft_print_status(philo, THINKING);
	}
	if (pthread_join(philo->philo_checker, NULL))
		ft_exit_error("Failed to join philo checking thread.", philo->data);
	return (NULL);
}

// ft_threads
// - saves the current timestamp (start of threaded philos);
// - starts threads for all philos carrying out routine;
// - joins threads upon completion;
int	ft_threads(t_data *data)
{
	int			i;

	data->time_of_start = ft_save_time();
	if (data->rounds_total != -1)
	{
		if (pthread_create(&data->round_checker, NULL, &ft_round_check, data))
			ft_exit_error("Failed to create round checking thread.", data);
	}
	i = -1;
	printf("[TIMESTAMP] \t [PHILOSOPHER] \t [STATUS]\n");
	while (++i < data->philos_total)
		ft_generate_thread(data, i);
	i = -1;
	while (++i < data->philos_total)
	{
		if (pthread_join(data->threads[i], NULL))
			ft_exit_error("Failed to join thread.", data);
	}
	if (data->rounds_total != -1)
	{
		if (pthread_join(data->round_checker, NULL))
			ft_exit_error("Failed to join round checking thread.", data);
	}
	return (0);
}
