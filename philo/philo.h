/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/03 16:44:05 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

//utils
int		ft_strlen(char *str);
char	**ft_split(char const *s, char c);
int		ft_atoi(char *str);

//printf err
void	print_err(int err_n);

//parsing funcs
int		not_valid(char *str);
int		is_empty(char *str);
int		contains_non_dig(char *str);

//used structs

typedef struct s_data
{
	int	args[5];
	int	nargs;
	int	philo_id;
}	t_data;

typedef struct s_vars
{
	int i;
	int	j;
	int k;
} t_vars;

#endif