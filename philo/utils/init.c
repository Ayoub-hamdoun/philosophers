/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:55:58 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/28 20:50:12 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(t_data *data, t_vars *vars)
{
	data->philo_count = vars->args[0];
	data->die_time = (long long)vars->args[1];
	data->eat_time = (long long)vars->args[2];
	data->sleep_time = (long long)vars->args[3];
	data->meal_limit = vars->args[4];
	data->start_time = get_current_time();
	data->total_meals = 0;
	data->finished = 0;
	data->meals_taken = 0;
	if (data->meal_limit != -1)
		data->total_meals = data->meal_limit * data->philo_count;
	return (0);
}

int	init_mtx(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(data->print_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(data->m_meals_taken), NULL))
		return (1);
	if (pthread_mutex_init(&(data->m_finished), NULL))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&(data->forks)[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philo(t_data *data, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!philo)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		(*philo)[i].data = data;
		(*philo)[i].id = i + 1;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % data->philo_count;
		(*philo)[i].last_meal = -1;
		(*philo)[i].meal_count = 0;
		if (pthread_mutex_init(&((*philo)[i].m_lastmeal), NULL))
			return (1);
		i++;
	}
	return (0);
}

void	cleaner(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(philos->m_lastmeal));
	pthread_mutex_destroy(&(data->print_lock));
	pthread_mutex_destroy(&(data->m_meals_taken));
	pthread_mutex_destroy(&(data->m_finished));
	free(philos);
	free(data->forks);
	return ;
}

int	init_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		philos[i].last_meal = get_current_time();
		if (pthread_create(&(philos[i].thread),
				NULL, philosopher_routine, &(philos[i])))
			return (1);
		i++;
	}
	philos_checker(data, philos);
	thread_joiner(data, philos);
	cleaner(data, philos);
	return (0);
}
