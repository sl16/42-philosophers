/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_watcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:05:19 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 22:55:30 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_died(t_philo *philo)
{
	uint64_t	curr_time;

	if (get_eating_flag(philo) == 1)
		return (1);
	curr_time = ft_save_time();
	if ((curr_time - philo->last_meal) >= philo->data->time_to_die)
	{
		set_death_flag(philo->data);
		ft_print_status(philo, DIE);
		pthread_mutex_unlock(&philo->lock_philo);
		return (0);
	}
	return (1);
}

int		watch_end(t_data *data)
{
	int	i;
	int	rounds_finished;

	i = 0;
	rounds_finished = 1;
	while (i < data->philos_total)
	{
		pthread_mutex_lock(&data->philos[i]->lock_philo);
		if (philo_died(data->philos[i]) == 0)
			return (0);
		if (data->rounds_total != -1)
		{
			if (data->philos[i]->rounds_eaten < data->rounds_total)
				rounds_finished = 0;
		}
		pthread_mutex_unlock(&data->philos[i]->lock_philo);
		i++;
	}
	if (data->rounds_total != -1 && rounds_finished == 1)
	{
		set_death_flag(data);
		return (0);
	}
	return (1);
}

void	*routine_watcher(void *data_ptr)
{
	t_data	*data;

	data = (t_data *) data_ptr;
	synchronize_start(data->time_of_start);
	while (1)
	{
		if (watch_end(data) == 0)
			return (NULL);
		ft_usleep(1);
	}
	return (NULL);
}