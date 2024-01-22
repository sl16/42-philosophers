/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:42:58 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 11:12:26 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	get_death_flag(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->lock_end);
	res = data->death_flag;
	pthread_mutex_unlock(&data->lock_end);
	return (res);
}

void	set_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->lock_end);
	data->death_flag = 1;
	pthread_mutex_unlock(&data->lock_end);
}