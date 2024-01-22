/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:19:01 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 19:51:52 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void	init_struct_data(t_data *data, int argc, char **argv)
{
	data->philos_total = ft_atoi(argv[1]);
	data->time_to_die = (uint64_t) ft_atoi(argv[2]);
	data->time_to_eat = (uint64_t) ft_atoi(argv[3]);
	data->time_to_sleep = (uint64_t) ft_atoi(argv[4]);
	if (argc == 6)
		data->rounds_total = ft_atoi(argv[5]);
	else
		data->rounds_total = -1;
	data->death_flag = 0;
	if (pthread_mutex_init(&data->lock_print, NULL) != 0)
			ft_exit_error("Failed to initiate the 'lock_print' mutex.", data);
	if (pthread_mutex_init(&data->lock_end, NULL) != 0)
			ft_exit_error("Failed to initiate the 'lock_end' mutex.", data);
}

t_philo	**init_struct_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->philos_total);
	if (!philos)
		ft_exit_error("Failed to allocate memory for 'philos array'.", data);
	i = 0;
	while (i < data->philos_total)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			ft_exit_error("Failed to allocate memory for 'philo'.", data);
		if (pthread_mutex_init(&philos[i]->lock_eating, NULL) != 0)
			ft_exit_error("Failed to initiate a 'lock_eating' mutex.", data);
		philos[i]->data = data;
		philos[i]->id = i;
		philos[i]->rounds_eaten = 0;
		place_forks(philos[i]);
		i++;
	}
	return (philos);
}

void	place_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % philo->data->philos_total;
	}
	else if (philo->id % 2 == 1)
	{
		philo->fork[0] = (philo->id + 1) % philo->data->philos_total;
		philo->fork[1] = philo->id;
	}
}

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc (sizeof(pthread_mutex_t) * data->philos_total);
	if (!forks)
		ft_exit_error("Failed to allocate memory for 'forks'.", data);
	i = 0;
	while (i < data->philos_total)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			ft_exit_error("Failed to initiate a 'fork' mutex.", data);
		i++;
	}
	return (forks);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	if (!data)
		ft_exit_error("Failed to allocate memory for 'data'.", NULL);
	init_struct_data(data, argc, argv);
	data->philos = init_struct_philos(data);
	data->locks_forks = init_forks(data);
	return (data);
}
