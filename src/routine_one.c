/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:20:12 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/17 22:20:45 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// ft_only_one
// - covers the case when only 1 philo is simulated;
int	ft_only_one(t_data *data)
{
	data->time_of_start = ft_save_time();
	printf("[TIMESTAMP] \t [PHILOSOPHER] \t [STATUS]\n");
	if (pthread_create(&data->threads[0], NULL,
			&ft_philosopher, &data->philos[0]))
		ft_exit_error("Failed to create thread.", data);
	while (get_death_flag(data) != 1)
		ft_usleep(1);
	pthread_join(data->threads[0], NULL);
	ft_free_all(data);
	exit (EXIT_SUCCESS);
}

// ft_routine_only_one
// - covers the case when only 1 philo is simulated;
void	ft_routine_only_one(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (get_death_flag(philo->data) != 1)
		ft_print_status(philo, FORK_EQUIP);
	while (get_death_flag(philo->data) != 1)
		ft_usleep(1);
	pthread_mutex_unlock(philo->fork_left);
}
