/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:13:40 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/28 20:33:24 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	start_sim(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&(data->m_finished));
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	printer(data, philo->id, "has taken a fork\n");
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	printer(data, philo->id, "has taken a fork\n");
	printer(data, philo->id, "is eating\n");
	pthread_mutex_lock(&(philo->m_lastmeal));
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&(philo->m_lastmeal));
	pthread_mutex_lock(&(data->m_meals_taken));
	data->meals_taken++;
	pthread_mutex_unlock(&(data->m_meals_taken));
	philo->meal_count++;
	ft_usleep(data->eat_time);
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
	printer(data, philo->id, "is sleeping\n");
	ft_usleep(data->sleep_time);
	printer(data, philo->id, "is thinking\n");
}

void	*philosopher_routine(void *arg)
{
	t_data	*data;
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
		start_sim(data, philo);
		ft_usleep(5);
	}
	return (0);
}

int	meals_count_check(t_data *data)
{
	if (data->meal_limit != -1 && data->meals_taken == data->total_meals)
	{
		pthread_mutex_lock(&data->m_finished);
		data->finished = 1;
		pthread_mutex_unlock(&data->m_finished);
		pthread_mutex_unlock(&(data->m_meals_taken));
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
	int			i;
	long long	current;

	while (!(data->finished))
	{
		pthread_mutex_lock(&(data->m_meals_taken));
		if (meals_count_check(data))
			break ;
		pthread_mutex_unlock(&(data->m_meals_taken));
		current = get_current_time();
		i = 0;
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
