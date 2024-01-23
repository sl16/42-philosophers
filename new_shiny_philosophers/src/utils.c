/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:44:17 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/23 16:04:56 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *nptr)
{
	int						sign;
	int						i;
	unsigned long long int	num;

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
	if (num > INT32_MAX)
		return (-1);
	return (sign * (int)num);
}

uint64_t	ft_save_time(void)
{
	struct timeval	tv;
	uint64_t		timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timestamp);
}

int	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = ft_save_time();
	while ((ft_save_time() - start) < time)
		usleep(1);
	return (0);
}

int	ft_print_status(t_philo	*philo, char *status)
{
	uint64_t	curr_time;

	pthread_mutex_lock(&philo->data->lock_print);
	if (get_death_flag(philo->data) == 1 && status[0] != 'd')
	{
		pthread_mutex_unlock(&philo->data->lock_print);
		return (0);
	}
	curr_time = ft_save_time() - philo->data->time_of_start;
	if (status[0] == 'd')
		ft_usleep(10);
	printf("%lu \t\t %d \t\t %s\n", curr_time, philo->id + 1, status);
	pthread_mutex_unlock(&philo->data->lock_print);
	return (0);
}

void	synchronize_start(uint64_t time_of_start)
{
	while (ft_save_time() < time_of_start)
		continue ;
}
