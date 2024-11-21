/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/10 16:10:33 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# define MAX 200

//used structs

// typedef struct s_philo t_philo;

typedef struct s_data t_data;
typedef struct s_fork
{
	int				id;
	pthread_mutex_t	frk_mtx;
}	t_fork;

typedef struct s_philo
{
	int				id;           // Philosopher ID
	int				meal_count;   // Meals eaten by the philosopher
	long long		last_meal;    // Time of the last meal
	int				dead;         // Death status of the philosopher
	pthread_t		thread;       // Philosopher thread
	t_fork			*left_fork;   // Left fork
	t_fork			*right_fork;  // Right fork
	t_data			*data;        // Pointer to shared data
} t_philo;

typedef struct s_data
{
	int				philo_count;  // Number of philosophers
	long long		die_time;     // Time until a philosopher dies
	long long		eat_time;     // Time a philosopher spends eating
	long long		sleep_time;   // Time a philosopher spends sleeping
	long long		start_time;   // Simulation start time
	int				meal_limit;   // Number of meals each philosopher must eat
	int				sim_end;      // Simulation termination flag
	int				total_meals;
	int				meals_taken;
	pthread_mutex_t	print_lock;   // Mutex for printing messages
	pthread_mutex_t	lock;
	pthread_t		monitor;
	t_fork			forks[MAX];       // Array of forks
	t_philo			philos[MAX];      // Array of philosophers
}	t_data;




typedef struct s_vars
{
	int	args[5];
	int	nargs;
	int i;
	int	j;
	int k;
}	t_vars;

//utils
int		ft_strlen(char *str);
char	**ft_split(char const *s, char c);
int		ft_atoi(char *str);
void	init_vars(t_vars *vars);
void	ft_print(char *str, t_data *data);

// simulation

void	*start_sim(void *philo);

//err/ cleaners
int		print_error(char *str, char **array);
void	free_2d(char **array);

//parsing funcs
int		not_valid(char *str);
int		is_empty(char *str);
int		contains_non_dig(char *str);
int		init_data(t_data *data, t_vars *vars);
int		pars_args(int ac, char *av[], t_vars *vars);

// time:
long long	get_current_time(void)
int			ft_usleep(long ms);

#endif