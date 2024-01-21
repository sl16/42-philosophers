/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:40:28 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 00:37:01 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INITIALIZE 	"initialized"
# define DIE			"died"
# define THINK			"is thinking"
# define FORK_EQUIP		"has taken a fork"
# define EAT			"is eating"
# define SLEEP			"is sleeping"

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h> // for uint64_t
# include <pthread.h> // for threads
# include <unistd.h> // for usleep
# include <sys/time.h> // for gettimeofday

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				rounds_eaten;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	lock_eating;
	uint64_t		death_timer;
}			t_philo;

typedef struct s_data
{
	struct s_philo	*philos;
	pthread_t		*threads;
	pthread_t		thread_watcher;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_end;
	int				philos_total;
	int				rounds_total;
	int				death_flag;
	uint64_t		time_of_start;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
}			t_data;



#endif