/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:05:53 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/15 10:07:38 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	get_eating_flag(t_philo *philo_ptr)
{
	int	res;

	pthread_mutex_lock(&philo_ptr->access_eating_flag);
	res = philo_ptr->eating_flag;
	pthread_mutex_unlock(&philo_ptr->access_eating_flag);
	return (res);
}

int	get_death_flag(t_data *data_ptr)
{
	int	res;

	pthread_mutex_lock(&data_ptr->access_death_flag);
	res = data_ptr->death_flag;
	pthread_mutex_unlock(&data_ptr->access_death_flag);
	return (res);
}

int	get_philos_finished(t_data *data_ptr)
{
	int	res;

	pthread_mutex_lock(&data_ptr->access_philos_finished);
	res = data_ptr->philos_finished;
	pthread_mutex_unlock(&data_ptr->access_philos_finished);
	return (res);
}
