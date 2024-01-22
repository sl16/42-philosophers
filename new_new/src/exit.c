/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:30:09 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 22:34:24 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_exit_error(char *error, t_data *data)
{
	printf("Error\n%s\n", error);
	if (data != NULL)
		free_data(data);
	exit (1);
}

int	free_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
	{
		while (i < data->philos_total)
		{
			if (&data->locks_forks[i])
				pthread_mutex_destroy(&data->locks_forks[i]);
			if (&data->philos[i]->lock_philo)
				pthread_mutex_destroy(&data->philos[i]->lock_eating);
			if (&data->philos[i]->lock_eating)
				pthread_mutex_destroy(&data->philos[i]->lock_eating);
			i++;
		}
	}
	if (&data->lock_end)
		pthread_mutex_destroy(&data->lock_end);
	if (&data->lock_print)
		pthread_mutex_destroy(&data->lock_print);
	return (0);
}

int	free_data(t_data *data)
{
	int	i;
	
	if (!data)
		return (0);
	if (data)
		free_mutexes(data);
	if (data->locks_forks)
		free(data->locks_forks);
	i = 0;
	if (data->philos)
	{
		while (i < data->philos_total)
		{
			if (data->philos[i])
				free(data->philos[i]);
			i++;
		}
		free(data->philos);
	}
	if (data)
		free(data);
	return (0);
}