/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:55:58 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/21 19:33:32 by ayhamdou         ###   ########.fr       */
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
	data->philo_count = vars->args[0];
	data->die_time = (long long)vars->args[1];
	data->eat_time = (long long)vars->args[2];
	data->sleep_time = (long long)vars->args[3];
	data->meal_limit = vars->args[4];
	data->start_time = get_current_time();
	data->total_meals = 0;
	data->finished = 0;
	data->finished_eat = 0;
	if (data->meal_limit != -1)
		data->total_meals = data->meal_limit * data->philo_count;
	return (0);
}

int init_mtx(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(data->print_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(data->m_finished_eat), NULL))
		return (1);
	if (pthread_mutex_init(&(data->m_finished), NULL))
		return (1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&(data->forks)[i], NULL) != 0)
			return(1);
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

void	printer(t_data *data, int philo_id, char *msg)
{
	pthread_mutex_lock(&(data->print_lock));
	pthread_mutex_lock(&(data->m_finished));
	if (!data->finished)
		printf("%lld %d %s", time_diff(data->start_time), philo_id, msg);
	pthread_mutex_unlock(&(data->m_finished));
	pthread_mutex_unlock(&(data->print_lock));
}

void	*philosopher_routine(void *arg)
{
	t_data *data;
	t_philo	*philo;

	philo = arg;
	data = philo->data;
	if (philo->id % 2)
		ft_usleep(50);
	while (1)
	{
		pthread_mutex_lock(&(data->m_finished));
		if (data->finished == 1)
		{
			pthread_mutex_unlock(&(data->m_finished));
			break ;
		}
		pthread_mutex_unlock(&(data->m_finished));
		pthread_mutex_lock(&(data->forks[philo->right_fork]));
		printer(data, philo->id, "took the right fork\n");
		pthread_mutex_lock(&(data->forks[philo->left_fork]));
		printer(data, philo->id, "took the left fork\n");
		printer(data, philo->id, "eating\n");
		pthread_mutex_lock(&(philo->m_lastmeal));
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(&(philo->m_lastmeal));
		pthread_mutex_lock(&(data->m_finished_eat));
		data->finished_eat++;
		pthread_mutex_unlock(&(data->m_finished_eat));
		philo->meal_count++;
		ft_usleep(data->eat_time);
		pthread_mutex_unlock(&(data->forks[philo->left_fork]));
		pthread_mutex_unlock(&(data->forks[philo->right_fork]));
		printer(data, philo->id, "sleeping\n");
		ft_usleep(data->sleep_time);
		printer(data, philo->id, "thinking\n");
		ft_usleep(5);
	}
	return (0);
}

int	meals_count_check(t_data *data)
{
	if (data->meal_limit != -1 && data->finished_eat == data->total_meals)
	{
		pthread_mutex_lock(&data->m_finished);
		data->finished = 1;
		pthread_mutex_unlock(&data->m_finished);
		pthread_mutex_unlock(&(data->m_finished_eat));
		return (1);
	}
	return (0);
}

int	is_dead(t_philo *philo, t_data *data, long long current)
{
	if (current - philo->last_meal >= data->die_time)
	{
		pthread_mutex_lock(&(data->m_finished));
		data->finished = 1;
		pthread_mutex_unlock(&(data->m_finished));
		pthread_mutex_unlock(&(philo->m_lastmeal));
		if (data->philo_count == 1)
			pthread_mutex_unlock(&(data->forks[philo->left_fork]));
		pthread_mutex_lock(&(philo->m_lastmeal));
		printf("%lld %d died\n", current - philo->last_meal, philo->id);
		pthread_mutex_unlock(&(philo->m_lastmeal));
		return (1);
	}
	return (0);
}

void	philos_checker(t_data *data, t_philo *philos)
{
	int	i;
	long long current;

	i = 0;
	while (!(data->finished))
	{
		pthread_mutex_lock(&(data->m_finished_eat));
		if (meals_count_check(data))
			break ;
		pthread_mutex_unlock(&(data->m_finished_eat));
		current = get_current_time();
		while (i < data->philo_count)
		{
			pthread_mutex_lock(&(philos[i].m_lastmeal));
			if (is_dead(&(philos[i]), data, current))
				break ;
			pthread_mutex_unlock(&(philos[i].m_lastmeal));
			i++;
		}
	}
}

void	pthread_joiner(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(philos[i].thread, NULL))
			printf("Error\n");
		i++;
	}
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
	pthread_mutex_destroy(&(data->m_finished_eat));
	pthread_mutex_destroy(&(data->m_finished));
	free(philos);
	free(data->forks);
	return ;
}

int init_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		philos[i].last_meal = get_current_time();
		if (pthread_create(&(philos[i].thread), NULL,
				philosopher_routine, &(philos[i])))
			return (1);
		i++;
	}
	philos_checker(data, philos);
	pthread_joiner(data, philos);
	cleaner(data, philos);
	return (0);
}
