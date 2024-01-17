/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:40:28 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/17 22:22:55 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INITIALIZED 	"initialized"
# define DIED			"died"
# define THINKING		"is thinking"
# define FORK_EQUIP		"has taken a fork"
# define EATING			"is eating"
# define SLEEPING		"is sleeping"

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h> // for uint64_t
# include <pthread.h> // for threads
# include <unistd.h> // for usleep
# include <sys/time.h> // for gettimeofday

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		philo_checker;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	access_philo;
	pthread_mutex_t	access_eating_flag;
	int				id;
	int				eating_flag;
	int				rounds_eaten;
	uint64_t		death_timer;
}			t_philo;

typedef struct s_data
{
	struct s_philo	*philos;
	pthread_t		*threads;
	pthread_t		round_checker;
	pthread_mutex_t	*forks;
	pthread_mutex_t	time_log;
	pthread_mutex_t	access_data;
	pthread_mutex_t	access_death_flag;
	pthread_mutex_t	access_philos_finished;
	pthread_mutex_t	create_thread_mutex;
	int				philos_total;
	int				rounds_total;
	int				philos_finished;	
	int				death_flag;
	uint64_t		time_of_start;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
}			t_data;

int			ft_init_data(t_data *data, int argc, char **argv);
int			ft_init_philos(t_data *data);
int			ft_init_forks(t_data *data);

int			ft_threads(t_data *data);
void		ft_generate_thread(t_data *data, int i);
void		ft_generate_checker(t_philo *philo);
void		*ft_philosopher(void *philo_ptr);
void		ft_eat(t_philo *philo);
void		*ft_philo_check(void *philo_ptr);
void		*ft_round_check(void *data_ptr);
int			ft_only_one(t_data *data);
void		ft_routine_only_one(t_philo *philo);
int			get_eating_flag(t_philo *philo_ptr);
int			get_death_flag(t_data *data_ptr);
int			get_philos_finished(t_data *data_ptr);
pthread_t	*get_thread(t_data *data_ptr, int i);

void		set_death_flag(t_data *data_ptr);
void		set_eating_flag_on(t_philo *philo_ptr);
void		set_eating_flag_off(t_philo *philo_ptr);

int			ft_check_args(int argc, char **argv);
int			ft_check_values(t_data *data);
int			ft_exit_error(char *error, t_data *data);
int			ft_print_status(t_philo	*philo, char *status);
int			ft_free_all(t_data *data);
int			ft_atoi(const char *nptr);
uint64_t	ft_save_time(void);
int			ft_usleep(uint64_t time);

#endif