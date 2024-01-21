/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:19:01 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 00:42:06 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Initializes the data structure with the provided arguments.
 * 
 * @param data The pointer to the data structure to be initialized.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 */
void	init_struct_data(t_data *data, int argc, char **argv)
{
	data->philos_total = ft_atoi(argv[1]);
	if (argc == 6)
		data->rounds_total = ft_atoi(argv[5]);
	else
		data->rounds_total = -1;
	data->death_flag = 0;
	data->time_to_die = (uint64_t) ft_atoi(argv[2]);
	data->time_to_eat = (uint64_t) ft_atoi(argv[3]);
	data->time_to_sleep = (uint64_t) ft_atoi(argv[4]);
	data->philos = malloc(sizeof(t_philo) * data->philos_total);
	if (!(data->philos))
		ft_exit_error("Failed to allocate memory for 'philos'.", data);
	data->threads = malloc(sizeof(pthread_t) * data->philos_total);
	if (!(data->threads))
		ft_exit_error("Failed to allocate memory for 'threads'.", data);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_total);
	if (!(data->forks))
		ft_exit_error("Failed to allocate memory for 'forks'.", data);
	pthread_mutex_init(&data->lock_end, NULL);
	pthread_mutex_init(&data->lock_print, NULL);
}

/**
 * Initializes the data structure for the philosophers.
 * 
 * @param data The pointer to the data structure.
 */
void	init_struct_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_total)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].rounds_eaten = 0;
		data->philos[i].death_timer = data->time_to_die;
		pthread_mutex_init(&data->philos[i].lock_eating, NULL);
		i++;
	}
}

/**
 * Initializes the forks for the philosophers.
 * 
 * This function initializes the mutex locks for the forks used by
 * the philosophers. It iterates over the total number of philosophers and
 * initializes a mutex lock for each fork. It also assigns the left and
 * right forks to each philosopher.
 * 
 * @param data A pointer to the data structure containing the philosophers
 * and forks.
 */
void init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_total)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 1;
	while (i < data->philos_total)
	{
		data->philos[i].fork_left = &data->forks[i];
		data->philos[i].fork_right = &data->forks[i - 1];
		i++;
	}
	data->philos[0].fork_left = &data->forks[0];
	data->philos[0].fork_right = &data->forks[data->philos_total - 1];
}

/**
 * @brief Initializes the data structure and sets up the program.
 * 
 * This function initializes the t_data structure with the provided command line arguments.
 * It also initializes the t_philo structures and the forks for the
 * philosophers.
 * 
 * @param data A pointer to the t_data structure.
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * @return 0 on success.
 */
int	init(t_data *data, int argc, char **argv)
{
	init_struct_data(data, argc, argv);
	init_struct_philos(data);
	init_forks(data);
	return (0);
}