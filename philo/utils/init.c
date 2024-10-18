/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:55:58 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/10/18 15:39:30 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_vars(t_vars *vars)
{
	int	i;

	i = 0;
	vars->i = 1;
	vars->j = 0;
	vars->k = 0;
	vars->nargs = 0;
	while (i < 4)
		vars->args[i++] = 0;
	vars->args[4] = -1;
}

int	init_data(t_data *data, t_vars *vars)
{
	int	i;
	int philo_nbr;
	t_philo *philo;

	i = 0;
	data->is_done = 0;
	data->n_philos = vars->args[0];
	data->time_die = (long)vars->args[1];
	data->time_eat = (long)vars->args[2];
	data->time_sleep = (long)vars->args[3];
	data->n_meals = vars->args[4];
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!(data->philos))
		return (1);
	data->forks = malloc(sizeof(t_fork) * data->n_philos);
	if (!(data->forks))
		return (1);
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (1);
		data->forks[i].id = i;
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->is_dead = 0;
		philo->data = data;
		philo_nbr = philo->data->n_philos;
	}
	return (0);
}
