/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:07:24 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/15 10:28:52 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// ft_exit_error
// - prints a custom error message, frees allocated system resources;
int	ft_exit_error(char *error, t_data *data)
{
	printf("Error\n%s\n", error);
	if (data != NULL)
		ft_free_all(data);
	exit (1);
}

// ft_check_args
// - checks for correct amount and format of arguments;
int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		ft_exit_error("Use 4 arguments (5th optional).", NULL);
	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				ft_exit_error("Provide digit arguments only.", NULL);
			j++;
		}
		i++;
	}
	return (0);
}

// ft_atoi
// - converts string to integers (helps with parsing arguments);
int	ft_atoi(const char *nptr)
{
	int		sign;
	int		i;
	int		num;

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
	return (sign * num);
}

// ft_save_time
// - gets time with system call 'gettimeofday' in seconds and microseconds;
// - returns a value converted to miliseconds;
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
