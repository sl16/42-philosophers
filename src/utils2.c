/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:02:52 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/15 10:43:36 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// ft_print_status
// - prints the current status of philosopher;
int	ft_print_status(t_philo	*philo, char *status)
{
	uint64_t	curr_time;

	curr_time = ft_save_time() - philo->data->time_of_start;
	pthread_mutex_lock(&philo->data->time_log);
	printf("%lu \t\t %d \t\t %s\n", curr_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->time_log);
	return (0);
}

// ft_only_one
// - covers the case when only 1 philo is simulated;
int	ft_only_one(t_data *data)
{
	data->time_of_start = ft_save_time();
	printf("[TIMESTAMP] \t [PHILOSOPHER] \t [STATUS]\n");
	if (pthread_create(&data->threads[0], NULL,
			&ft_philosopher, &data->philos[0]))
		ft_exit_error("Failed to create thread.", data);
	while (get_death_flag(data) != 1)
		ft_usleep(1);
	pthread_join(data->threads[0], NULL);
	ft_free_all(data);
	exit (EXIT_SUCCESS);
}

// ft_routine_only_one
// - covers the case when only 1 philo is simulated;
void	ft_routine_only_one(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (get_death_flag(philo->data) != 1)
		ft_print_status(philo, FORK_EQUIP);
	while (get_death_flag(philo->data) != 1)
		ft_usleep(1);
	pthread_mutex_unlock(philo->fork_left);
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
	if (data->philos)
		free(data->philos);
	if (data->threads)
		free(data->threads);
	if (data->forks)
		free(data->forks);
	return (0);
}

// ft_generate_thread
// - creates a philo thread;
// - separated from ft_threads for norminette reasons;
void	ft_generate_thread(t_data *data, int i)
{
	if (pthread_create(&data->threads[i], NULL,
			&ft_philosopher, &data->philos[i]))
		ft_exit_error("Failed to create thread.", data);
}
