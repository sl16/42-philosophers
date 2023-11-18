/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:31:45 by vbartos           #+#    #+#             */
/*   Updated: 2023/11/16 16:16:21 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	get_philos_finished(t_data *data_ptr)
{
	int	res;
	
	pthread_mutex_lock(&data_ptr->access_philos_finished);
	res = data_ptr->philos_finished;
	pthread_mutex_unlock(&data_ptr->access_philos_finished);
	return (res);
}
