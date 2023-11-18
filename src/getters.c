/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:05:53 by vbartos           #+#    #+#             */
/*   Updated: 2023/11/16 16:24:06 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int		get_eating_flag(t_philo *philo_ptr)
{
	int	res;

	pthread_mutex_lock(&philo_ptr->access_eating_flag);
	res = philo_ptr->eating_flag;
	pthread_mutex_unlock(&philo_ptr->access_eating_flag);
	return (res);
}

int		get_death_flag(t_data *data_ptr)
{
	int	res;
	
	pthread_mutex_lock(&data_ptr->access_death_flag);
	res = data_ptr->death_flag;
	pthread_mutex_unlock(&data_ptr->access_death_flag);
	return (res);
}

// int		get_rounds_eaten(t_philo *philo_ptr)
// {
// 	int	res;

// 	pthread_mutex_lock(&philo_ptr->access_philo);
// 	res = philo_ptr->rounds_eaten;
// 	pthread_mutex_unlock(&philo_ptr->access_philo);
// 	return (res);
// }

// uint64_t	get_death_timer(t_philo *philo_ptr)
// {
// 	uint64_t	res;

// 	pthread_mutex_lock(&philo_ptr->access_philo);
// 	res = philo_ptr->death_timer;
// 	pthread_mutex_unlock(&philo_ptr->access_philo);
// 	return (res);
// }

// uint64_t	get_time_of_start(t_data *data_ptr)
// {
// 	uint64_t	res;

// 	pthread_mutex_lock(&data_ptr->access_data);
// 	res = data_ptr->time_of_start;
// 	pthread_mutex_unlock(&data_ptr->access_data);
// 	return (res);
// }
