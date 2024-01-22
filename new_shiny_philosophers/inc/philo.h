/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:40:28 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 17:43:03 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	pthread_t		thread;
	int				id;
	int				rounds_eaten;
	int				fork[2];
	pthread_mutex_t	lock_eating;
	uint64_t		last_meal;
}			t_philo;

typedef struct s_data
{
	struct s_philo	**philos;
	pthread_t		watcher_thread;
	pthread_mutex_t	*locks_forks;
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

int 		check_input(int argc, char **argv);
void 		check_values(char *arg, int i);
void 		check_intmax(char *arg);
void 		check_format(char *arg);
void 		check_args(int argc);

t_data		*init_data(int argc, char **argv);
void		init_struct_data(t_data *data, int argc, char **argv);
t_philo		**init_struct_philos(t_data *data);
pthread_mutex_t	*init_forks(t_data *data);
void		place_forks(t_philo *philo);

int			simulation_start(t_data *data);
int 		simulation_end(t_data *data);

void		*routine_philo(void *philo_ptr);
void		*routine_one(t_philo *philo);
void		action_eat(t_philo *philo);
void		action_sleep(t_philo *philo, int64_t philo_sleep_time);
void		action_think(t_philo *philo, int visibility);

void		*routine_watcher(void *data_ptr);
int			watch_end(t_data *data);
int			philo_died(t_philo *philo);

int			get_death_flag(t_data *data);
void		set_death_flag(t_data *data);

int			ft_atoi(const char *nptr);
uint64_t	ft_save_time(void);
int			ft_usleep(uint64_t time);
void		synchronize_start(uint64_t time_of_start);
int			ft_print_status(t_philo	*philo, char *status);

int			ft_exit_error(char *error, t_data *data);
int			free_data(t_data *data);

#endif