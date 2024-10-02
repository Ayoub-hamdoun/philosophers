/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/10/02 12:15:14 by ayhamdou         ###   ########.fr       */
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

typedef struct s_philo t_philo;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_data
{
	int		n_philos;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		n_meals;
	long	start_sim;
	int		end_sim;
	t_fork	*forks;
	t_philo	*philos;
}	t_data;

struct s_philo
{
	int			id;
	int			num_meals;
	long		time_lmeal;
	int			is_dead;
	pthread_t	philo_thread;
	t_fork		*l_fork;
	t_fork		*r_fork;
	t_data		*data;
};

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

//err/ cleaners
int		print_error(char *str, char **array);
void	free_2d(char **array);

//parsing funcs
int		not_valid(char *str);
int		is_empty(char *str);
int		contains_non_dig(char *str);
int		init_data(t_data *data, t_vars *vars);
int		pars_args(int ac, char *av[], t_vars *vars);


#endif