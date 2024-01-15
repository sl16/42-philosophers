/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:45:18 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/15 10:07:51 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_death_flag(t_data *data_ptr)
{
	pthread_mutex_lock(&data_ptr->access_death_flag);
	data_ptr->death_flag = 1;
	pthread_mutex_unlock(&data_ptr->access_death_flag);
}

void	set_eating_flag_on(t_philo *philo_ptr)
{
	pthread_mutex_lock(&philo_ptr->access_eating_flag);
	philo_ptr->eating_flag = 1;
	pthread_mutex_unlock(&philo_ptr->access_eating_flag);
}

void	set_eating_flag_off(t_philo *philo_ptr)
{
	pthread_mutex_lock(&philo_ptr->access_eating_flag);
	philo_ptr->eating_flag = 0;
	pthread_mutex_unlock(&philo_ptr->access_eating_flag);
}
