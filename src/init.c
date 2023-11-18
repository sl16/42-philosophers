/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:19:01 by vbartos           #+#    #+#             */
/*   Updated: 2023/11/16 16:15:29 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// ft_init_data
// - initializes general struct that holds all rules and
// pointers to philosophers, mallocs for threads and mutexes;
int	ft_init_data(t_data *data, int argc, char **argv)
{
	data->philos_total = ft_atoi(argv[1]);
	if (argc == 6)
		data->rounds_total = ft_atoi(argv[5]);
	else
		data->rounds_total = -1;
	data->philos_finished = 0;
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
	pthread_mutex_init(&data->time_log, NULL);
	pthread_mutex_init(&data->access_data, NULL);
	pthread_mutex_init(&data->access_death_flag, NULL);
	pthread_mutex_init(&data->access_philos_finished, NULL);
	return (0);
}

// ft_init_philos
// - initializes structs for N philosophers;
int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_total)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eating_flag = 0;
		data->philos[i].rounds_eaten = 0;
		data->philos[i].death_timer = data->time_to_die;
		pthread_mutex_init(&data->philos[i].access_philo, NULL);
		pthread_mutex_init(&data->philos[i].access_eating_flag, NULL);
		i++;
	}
	return (0);
}

// ft_init_forks
// - initializes N mutexes;
// - assigns mutexes as right and left forks;
int	ft_init_forks(t_data *data)
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
	return (0);
}

// ft_check_values
// - checks that values input via arguments are valid;
int	ft_check_values(t_data *data)
{
	if (data->philos_total < 1
		|| data->philos_total > 200
		|| data->rounds_total == 0
		|| data->time_to_die < 1
		|| data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		ft_exit_error("Provided values are not valid.", data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_check_args(argc, argv);
	ft_init_data(&data, argc, argv);
	ft_check_values(&data);
	ft_init_philos(&data);
	ft_init_forks(&data);
	if (data.philos_total == 1)
		ft_only_one(&data);
	ft_threads(&data);
	ft_free_all(&data);
	return (0);
}
