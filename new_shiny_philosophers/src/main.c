/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:14:05 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 00:49:47 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	check_input(argc, argv);
	init(data, argc, argv);
	if (data->philos_total == 1)
		simulation_one();
	else
		simulation_standard();

	// ft_init_data(&data, argc, argv);
	// ft_check_values(&data);
	// ft_init_philos(&data);
	// ft_init_forks(&data);
	// if (data.philos_total == 1)
	// 	ft_only_one(&data);
	// ft_threads(&data);
	// ft_free_all(&data);
	// return (0);
}
