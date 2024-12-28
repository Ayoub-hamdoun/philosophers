/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/28 20:50:42 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

//used structs

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meal_count;
	long long		last_meal;
	pthread_mutex_t	m_lastmeal;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	long long		start_time;
	int				meal_limit;
	int				sim_end;
	int				total_meals;
	int				meals_taken;
	int				finished;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	m_meals_taken;
	pthread_mutex_t	m_finished;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	t_philo			*philos;
}	t_data;

typedef struct s_vars
{
	int	args[5];
	int	nargs;
	int	i;
	int	j;
	int	k;
}	t_vars;

//utils
int			ft_strlen(char *str);
char		**ft_split(char const *s, char c);
int			ft_atoi(char *str);
void		init_vars(t_vars *vars);
void		printer(t_data *data, int philo_id, char *msg);

// init
int			init_mtx(t_data *data);
int			init_data(t_data *data, t_vars *vars);
int			init_philo(t_data *data, t_philo **philo);
int			init_threads(t_data *data, t_philo *philos);

// simulation
void		start_sim(t_data *data, t_philo *philo);
void		*philosopher_routine(void *arg);
int			meals_count_check(t_data *data);
int			is_dead(t_philo *philo, t_data *data, long long current);
void		philos_checker(t_data *data, t_philo *philos);

//err/ cleaners
int			print_error(char *str, char **array);
void		free_2d(char **array);
void		cleaner(t_data *data, t_philo *philos);
void		thread_joiner(t_data *data, t_philo *philos);

//parsing funcs
int			not_valid(char *str);
int			is_empty(char *str);
int			contains_non_dig(char *str);
int			pars_args(int ac, char *av[], t_vars *vars);

// time:
long long	get_current_time(void);
int			ft_usleep(long ms);
long long	time_diff(long long start_sim);

#endif