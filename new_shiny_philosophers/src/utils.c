/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:44:17 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 00:46:31 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// ft_atoi
// - converts string to integers (helps with parsing arguments);
int	ft_atoi(const char *nptr)
{
	int		sign;
	int		i;
	unsigned long long int		num;

	i = 0;
	num = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t'
		|| nptr[i] == '\f' || nptr[i] == '\r'
		|| nptr[i] == '\n' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign = sign * -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	if (i > INT8_MAX)
		return (-1);
	return (sign * (int)num);
}

uint64_t	ft_save_time(void)
{
	struct timeval	tv;
	uint64_t		timestamp;

	if (gettimeofday(&tv, NULL))
		ft_exit_error("Couldn't save current time.", NULL);
	timestamp = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (timestamp);
}

// ft_usleep
// - mimics system call usleep, but is more precise;
int	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = ft_save_time();
	while ((ft_save_time() - start) < time)
		usleep(time / 10);
	return (0);
}

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