/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:30:09 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 00:46:16 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_exit_error(char *error, t_data *data)
{
	printf("Error\n%s\n", error);
	if (data != NULL)
		ft_free_all(data);
	exit (1);
}

// ft_free_all
// - frees all alloc'd memory and mutexes;
int	ft_free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_total)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].access_philo);
		pthread_mutex_destroy(&data->philos[i].access_eating_flag);
		i++;
	}
	pthread_mutex_destroy(&data->access_data);
	pthread_mutex_destroy(&data->access_death_flag);
	pthread_mutex_destroy(&data->access_philos_finished);
	pthread_mutex_destroy(&data->time_log);
	pthread_mutex_destroy(&data->create_thread_mutex);
	if (data->philos)
		free(data->philos);
	if (data->threads)
		free(data->threads);
	if (data->forks)
		free(data->forks);
	return (0);
}