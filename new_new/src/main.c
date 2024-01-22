/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:14:05 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 22:20:44 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	simulation_start(t_data *data)
{
	int			i;

	data->time_of_start = ft_save_time() + (data->philos_total * 10);
	printf("[TIMESTAMP] \t [PHILOSOPHER] \t [STATUS]\n");
	i = 0;
	while (i < data->philos_total)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&routine_philo, data->philos[i]))
			ft_exit_error("Failed to create a philo thread.", data);
		i++;
	}
	if (data->philos_total > 1)
	{
		if (pthread_create(&data->watcher_thread, NULL,
				&routine_watcher, data))
			ft_exit_error("Failed to create the watcher thread.", data);
	}
	return (0);
}

int simulation_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_total)
	{
		if (pthread_join(data->philos[i]->thread, NULL))
			ft_exit_error("Failed to join a philo thread.", data);
		i++;
	}
	if (data->philos_total > 1)
	{
		if (pthread_join(data->watcher_thread, NULL))
			ft_exit_error("Failed to join the watcher thread.", data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	check_input(argc, argv);
	data = init_data(argc, argv);
	simulation_start(data);
	simulation_end(data);
	free_data(data);
	return (0);
}
