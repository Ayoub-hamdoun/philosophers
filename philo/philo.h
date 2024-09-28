/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/28 15:21:41 by ayhamdou         ###   ########.fr       */
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

typedef struct s_data
{
	int	n_philos;
	int time_die;
	int	time_eat;
	int	time_sleep;
	int	n_meals;
}	t_data;

typedef struct s_philo{
	int	id;
}	t_philo;

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
int		pars_args(int ac, char *av[], t_vars *vars);


#endif